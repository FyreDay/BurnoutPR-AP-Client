#pragma once
#include <cstdint>


#define PTR(type, name, offset) \
        type* name() { return *reinterpret_cast<type**>((uintptr_t)this + offset); }

#define VALUE(type, name, offset) \
        type& name() { return *reinterpret_cast<type*>((uintptr_t)this + offset); }

#define ARRAY_REF(type, count, name, offset) \
    type (&name())[count] { return *reinterpret_cast<type(*)[count]>((uintptr_t)this + offset); }

extern uintptr_t moduleBase;

namespace Core {


    //Game Static Ptrs
    static constexpr uintptr_t BrnGameModulePtr = 0x013FC8E0;

    static constexpr size_t VehicleListEntrySize = 0x108;
    static constexpr size_t WheelListEntrySize = 0x48;
    //enums
    enum VehicleManufacturer
    {
        Carson = 0,
        Hunter,
        Jansen,
        Krieger,
        Kitano,
        Montgomery,
        Nakamura,
        Rossolini,
        Watson
    };

    enum LiveryType
    {
        Finish = 0,
        ParentFinish = 1,
        FinishAlt = 2,
        Platinum = 3,
        Gold = 4,
        Community = 5
    };

    //structs

    struct VehicleListEntry
    {
        VALUE(uint64_t, VehicleID, 0x00)
        VALUE(uint64_t, ParentVehicleID, 0x08)

        ARRAY_REF(char, 64, FallbackName, 0x30)
             
        VALUE(float, DamageLimit, 0x90)

        VALUE(uint8_t, Speed, 0x99)
        VALUE(uint8_t, Strength, 0x9B)

        VALUE(uint8_t, LiveryType, 0xFD)
    };

    struct WheelListEntry
    {
        VALUE(uint64_t, WheelID, 0x00)
        ARRAY_REF(char, 64, name, 0x08)
    };


    struct VehicleListResource
    {
        VALUE(uint32_t, VehicleCount, 0x0)
        PTR(VehicleListEntry, Entries, 0x4)
    };

    struct WheelListResource
    {
        VALUE(uint32_t, WheelCount, 0x0)
        PTR(WheelListEntry, Entries, 0x4)
    };

    struct RaceCar
    {
        VALUE(uint64_t, VehicleID, 0x68)
        VALUE(uint64_t, WheelID, 0x70)

        VALUE(int32_t, ColorIndex, 0x94)
        VALUE(int32_t, ColorPaletteType, 0x98)

        VALUE(int32_t, VehicleType, 0xA4)
    };


    struct ActiveRaceCar
    {
        PTR(RaceCar, RaceCarPtr, 0x7C0)

        VALUE(float, Deformation, 0x8AC)

        ARRAY_REF(float,3, PaintColor, 0x1480)
        ARRAY_REF(float,3, PearlColor, 0x1490)
    };
    
    //Game module

    struct BrnGameModule
    {
        VALUE(int32_t, BoostType, 0x3FFD4)

        VALUE(int32_t, BoostLevel, 0x40754)
        VALUE(int32_t, BoostLossLevel, 0x40758)

        VALUE(int32_t, PlayerVehicleIndex, 0x40C28)

        VALUE(int32_t, GameModeType, 0x69D58C)

        VALUE(bool, ChallengeTimerRunning, 0x6A4104)

        PTR(void, CurrentFreeburnGame, 0x6EBE50)

        VALUE(bool, IsOnline, 0xB6D415)

        VALUE(int32_t, PlayerVehicleDriverArray, 0x61BCD8) //start of array
        
        ActiveRaceCar* GetActiveRaceCar()
        {
            return *(ActiveRaceCar**)((uintptr_t)this + 0x12980 + PlayerVehicleIndex() * 0x4180);
        }
    };

    inline BrnGameModule* GetGameModule()
    {
        return *(BrnGameModule**)BrnGameModulePtr;
    }
}

