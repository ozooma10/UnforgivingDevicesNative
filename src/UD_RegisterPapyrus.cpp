#include <UD_RegisterPapyrus.h>
#include <UD_MinigameEffect.h>
#include <UD_Utility.h>
#include <UD_UI.h>
#include <UD_Inventory.h>

namespace UD
{
    #define REGISTERPAPYRUSFUNC(name,unhook) vm->RegisterFunction(#name, "UD_Native", UD::name,unhook);

    bool RegisterPapyrusFunctions(RE::BSScript::IVirtualMachine *vm) {
        REGISTERPAPYRUSFUNC(StartMinigameEffect,true)
        REGISTERPAPYRUSFUNC(EndMinigameEffect,true)
        REGISTERPAPYRUSFUNC(IsMinigameEffectOn,true)
        REGISTERPAPYRUSFUNC(UpdateMinigameEffectMult,true)
        REGISTERPAPYRUSFUNC(ToggleMinigameEffect,true)
        REGISTERPAPYRUSFUNC(MinigameStatsCheck,true)
        REGISTERPAPYRUSFUNC(MinigameEffectSetHealth,true)
        REGISTERPAPYRUSFUNC(MinigameEffectSetStamina,true)
        REGISTERPAPYRUSFUNC(MinigameEffectSetMagicka,true)
        REGISTERPAPYRUSFUNC(MinigameEffectUpdateHealth,true)
        REGISTERPAPYRUSFUNC(MinigameEffectUpdateStamina,true)
        REGISTERPAPYRUSFUNC(MinigameEffectUpdateMagicka,true)

        //UTILITY
        REGISTERPAPYRUSFUNC(CodeBit,true)
        REGISTERPAPYRUSFUNC(DecodeBit,true)
        REGISTERPAPYRUSFUNC(iRange,true)
        REGISTERPAPYRUSFUNC(fRange,true)
        REGISTERPAPYRUSFUNC(Round,true)
        REGISTERPAPYRUSFUNC(IsPlayer,true)
        REGISTERPAPYRUSFUNC(GetActorName,true)

        //UI
        REGISTERPAPYRUSFUNC(AddMeterEntryIWW,true)
        REGISTERPAPYRUSFUNC(RemoveMeterEntryIWW,true)
        REGISTERPAPYRUSFUNC(ToggleMeterIWW,true)
        REGISTERPAPYRUSFUNC(SetMeterRateIWW,true)
        REGISTERPAPYRUSFUNC(SetMeterMultIWW,true)
        REGISTERPAPYRUSFUNC(SetMeterValueIWW,true)
        REGISTERPAPYRUSFUNC(UpdateMeterValueIWW,true)
        REGISTERPAPYRUSFUNC(GetMeterValueIWW,true)

        REGISTERPAPYRUSFUNC(AddMeterEntrySkyUi,true)
        REGISTERPAPYRUSFUNC(RemoveMeterEntrySkyUi,true)
        REGISTERPAPYRUSFUNC(ToggleMeterSkyUi,true)
        REGISTERPAPYRUSFUNC(SetMeterRateSkyUi,true)
        REGISTERPAPYRUSFUNC(SetMeterMultSkyUi,true)
        REGISTERPAPYRUSFUNC(SetMeterValueSkyUi,true)
        REGISTERPAPYRUSFUNC(UpdateMeterValueSkyUi,true)
        REGISTERPAPYRUSFUNC(GetMeterValueSkyUi,true)

        REGISTERPAPYRUSFUNC(ToggleAllMeters,true)
        REGISTERPAPYRUSFUNC(RemoveAllMeterEntries,true)

        //Inventory
        REGISTERPAPYRUSFUNC(GetInventoryDevices,true)
        REGISTERPAPYRUSFUNC(GetRenderDevices,true)
        REGISTERPAPYRUSFUNC(GetSharpestWeapon,true)

        //animation
        REGISTERPAPYRUSFUNC(GetActorConstrains,true)

        //skill
        REGISTERPAPYRUSFUNC(CalculateSkillFromPerks,true)

        //modifiers
        REGISTERPAPYRUSFUNC(GetModifierAllParam,true)
        REGISTERPAPYRUSFUNC(GetStringParamInt,true)
        REGISTERPAPYRUSFUNC(GetStringParamFloat,true)
        REGISTERPAPYRUSFUNC(GetStringParamString,true)

        //actor slot manager
        REGISTERPAPYRUSFUNC(RegisterSlotQuest,true)
        REGISTERPAPYRUSFUNC(GetRegisteredActors,true)

        ORS::OrgasmManager::GetSingleton()->RegisterPapyrusFunctions(vm);

        return true;
    }

    #undef REGISTERPAPYRUSFUNC
}
