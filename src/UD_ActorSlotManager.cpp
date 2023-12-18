#include <UD_ActorSlotManager.h>

SINGLETONBODY(UD::ActorSlotManager)

void UD::ActorSlotManager::Setup()
{
    if (_installed) return;
    _installed = true;
}

void UD::ActorSlotManager::Update()
{
    ValidateAliases();

    if (_slots == nullptr) return;

    UniqueLock lock(_lock);
    for (auto&& [actor,slot] : *_slots)
    {
        //LOG("Updating {}",it.first->GetName())
        slot.BestWeapon = InventoryHandler::GetSingleton()->GetSharpestWeapon(actor);
    }
}

std::vector<RE::ActorHandle::native_handle_type> UD::ActorSlotManager::GetValidActors()
{
    UniqueLock lock(_lock);
    if (_slots == nullptr) return std::vector<RE::ActorHandle::native_handle_type>();
    if (_slots->size() + _closeactors.size() == 0) return std::vector<RE::ActorHandle::native_handle_type>();
    //combine to one result
    std::vector<RE::ActorHandle::native_handle_type> loc_res(_slots->size() + _closeactors.size());

    int loc_i = 0;
    for (auto&& it : *_slots)
    {
        loc_res[loc_i] = it.first->GetHandle().native_handle();
        loc_i++;
    }
    for (auto&& it : _closeactors)
    {
        loc_res[loc_i] = it.native_handle();
        loc_i++;
    }
    return loc_res;
}

std::vector<RE::Actor*> UD::ActorSlotManager::GetRegisteredActors()
{
    UniqueLock lock(_lock);
    if (_slots == nullptr) return std::vector<RE::Actor*>();
    
    std::vector<RE::Actor*> loc_result;

    for (auto&& it : *_slots)
    {
        loc_result.push_back(it.first);
    }
    return loc_result;
}

UD::ActorStorage* UD::ActorSlotManager::GetActorStorage(RE::Actor* a_actor)
{
    UniqueLock lock(_lock);
    return (_slots && a_actor) ? &(*_slots)[a_actor] : nullptr;
}

bool UD::ActorSlotManager::RegisterSlotQuest(RE::TESQuest* a_quest)
{
    UniqueLock lock(_lock);
    if (a_quest == nullptr) return false;
    if (std::find(_slotquests.begin(),_slotquests.end(),a_quest) == _slotquests.end())
    {
        _slotquests.push_back(a_quest);
        LOG("ActorSlotManager::RegisterSlotQuest({}) - Total number = {}",a_quest->GetName(),_slotquests.size())
        //ValidateAliases();
        return true;
    }
    else
    {
        return false;
    }
}

void UD::ActorSlotManager::ValidateAliases()
{
    UniqueLock lock(_lock);
    std::unordered_map<RE::Actor*,ActorStorage>* loc_slots = new std::unordered_map<RE::Actor*,ActorStorage>();

    for (auto&& it1 : _slotquests)
    {
        auto loc_aliases = it1->refAliasMap;
        for (auto&& it2 : loc_aliases)
        {
            RE::Actor* loc_actor = reinterpret_cast<RE::Actor*>(it2.second.get().get());
            if (loc_actor == nullptr) continue;  //skip empty slot

            //LOG("ActorSlotManager::ValidateAliases() - Checking actor {}",loc_actor->GetName())

            if (_slots && (_slots->find(loc_actor) == _slots->end()))
            {
                //exist, copy it
                memcpy(&(*loc_slots)[loc_actor],&(*_slots)[loc_actor],sizeof(ActorStorage));
            }
            else
            {
                (*loc_slots)[loc_actor] = ActorStorage();
            }
        }
    }
    delete _slots;
    _slots = loc_slots;

    static RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton();

    _closeactors.clear();
    const int loc_distance = UD::Config::GetSingleton()->GetVariable<int>("General.iUpdateDistance",5000);
    RE::TES::GetSingleton()->ForEachReferenceInRange(loc_player, loc_distance, [&](RE::TESObjectREFR& a_ref) {
        auto loc_refBase    = a_ref.GetBaseObject();
        auto loc_actor      = a_ref.As<RE::Actor>();
        if (loc_actor && !loc_actor->IsDisabled() && 
            loc_actor->Is3DLoaded() && 
            loc_actor != loc_player &&
            (a_ref.Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC)) &&
            _slots->find(loc_actor) == _slots->end() //only if actor is not already registered
           )
        ) 
        {
            _closeactors.push_back(loc_actor->GetHandle());
        }
        return RE::BSContainer::ForEachResult::kContinue;
    });

    LOG("Registered actors")
    for (auto&& it : *_slots) LOG("\t{}",it.first->GetName())

    LOG("Close actors")
    for (auto&& it : _closeactors) LOG("\t{}",it.get().get()->GetName())

}
