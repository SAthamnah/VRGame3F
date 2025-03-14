#include "TsCore.h"
#include "ts_api/ts_core_api.h"

TsCore::TsCore()
{
    UE_LOG(LogTemp, Log, TEXT("TsCore: constructed."));
}

bool TsCore::Load()
{
    Loader.Load();
    return Loader.IsLoaded();
}

void TsCore::Unload()
 {
    if (!Loader.IsLoaded())
    {
        return;
    }
    Loader.Unload();
 }

bool TsCore::Initialize()
{
    if (bIsInitialized)
    {
        UE_LOG(LogTemp, Log, TEXT("TsCore: already initialized."));
        return bIsInitialized;
    }

    auto InitializeFn = reinterpret_cast<decltype(&ts_initialize)>(FPlatformProcess::GetDllExport(Loader.GetLibHandle(), *FString("ts_initialize")));
    if (InitializeFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsCore: can't initialize - null ts_initialize handle."));
        return bIsInitialized;
    }

    int status = InitializeFn();
    if (status >= 0)
    {
        bIsInitialized = true;
        UE_LOG(LogTemp, Log, TEXT("TsCore: initialized."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TsCore: can't initialize: %d."), status);
    }
    return bIsInitialized;
}

void* TsCore::GetLibHandle() const
{
    return Loader.GetLibHandle();
}

void TsCore::Uninitialize()
{
    if (!bIsInitialized)
    {
        UE_LOG(LogTemp, Log, TEXT("TsCore: was not initialized."));
        return;
    }

    auto UninitializeFn = reinterpret_cast<decltype(&ts_uninitialize)>(FPlatformProcess::GetDllExport(Loader.GetLibHandle(), *FString("ts_uninitialize")));
    if (UninitializeFn != nullptr)
    {
        UninitializeFn();
        bIsInitialized = false;
        UE_LOG(LogTemp, Log, TEXT("TsCore: uninitialized."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TsCore: can't uninitialize - null ts_uninitialize handle."));
    }
}

bool TsCore::IsInitialized()
{
    return bIsInitialized;
}

TsCore::~TsCore()
{
    UE_LOG(LogTemp, Log, TEXT("TsCore: deconstructed."));
}
