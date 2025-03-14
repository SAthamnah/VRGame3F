#include "Teslasuit.h"

#define LOCTEXT_NAMESPACE "FTeslasuitModule"

void FTeslasuitModule::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("FTeslasuitModule: startup module"));

    Core = std::make_unique<TsCore>();

    if (Core->Load() && Core->Initialize())
    {
        DeviceProvider = std::make_unique<TsDeviceProvider>();
        DeviceProvider->SetLibHandle(GetLibHandle());

        HapticAssetManager = std::make_unique<TsHapticAssetManager>();
        HapticAssetManager->SetLibHandle(GetLibHandle());

        DeviceProvider->Start();
    }
}

void FTeslasuitModule::ShutdownModule()
{
    HapticAssetManager.reset();

    if (DeviceProvider)
    {
        DeviceProvider->Stop();
        DeviceProvider.reset();
    }

    if (Core->GetLibHandle())
    {
        Core->Uninitialize();
        Core->Unload();
        Core.reset();
    }
}

void* FTeslasuitModule::GetLibHandle() const
{
    return Core->GetLibHandle();
}

TsDeviceProvider& FTeslasuitModule::GetDeviceProvider()
{
    return *DeviceProvider;
}

TsHapticAssetManager& FTeslasuitModule::GetHapticAssetManager()
{
    return *HapticAssetManager;
}

bool FTeslasuitModule::IsInitialized()
{
    return Core->IsInitialized();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTeslasuitModule, Teslasuit)
