#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "TsLoader.h"

/**
 * \addtogroup core
 * @{
 */

/*!
	\brief Manages loading of Teslasuit library and core C API initialization.

	Class shouldn't be used directly.
	#FTeslasuitModule creates an instance of this class in order to load
	Teslasuit C API library and initialize C API as required.
*/
class TESLASUIT_API TsCore
{
public:
	/*!
		\brief Core constructor.
	*/
	TsCore();

	/*!
		\brief Core destructor.
	*/
	~TsCore();

	/*!
		\brief Loads the library.
	*/
	bool Load();

	/*!
		\brief Unloads the library.
	*/
	void Unload();

	/*!
		\brief Initializes Teslasuit API.
	*/
	bool Initialize();

	/*!
		\brief Deinitializes Teslasuit API.
	*/
	void Uninitialize();

	/*!
		\brief Returns raw pointer to the Teslasuit library.
	*/
	void* GetLibHandle() const;

	/*!
		\brief Returns init status of the Teslasuit library.
	*/
	bool IsInitialized();

private:
	TsLoader Loader;
	bool bIsInitialized = false;
};

/**@}*/
