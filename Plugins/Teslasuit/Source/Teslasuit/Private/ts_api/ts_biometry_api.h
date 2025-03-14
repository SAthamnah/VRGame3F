#pragma once
#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup biometry Biometry API
    The Biometry module provides functions to receive EMG data, PPG raw and processed data, BIA data.

    The common flow is to set data update callback, then start streaming. After the start, data update will be received in a registered callback.
    After finishing should be called stop streaming.
 * @{
 */

/*!
    \brief Sets EMG data update callback.

    After a callback was set, streaming can be started with #ts_emg_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] ts_callback callback with #TsEmgData
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_set_update_callback(TsDeviceHandle* dev, 
    TsEmgUpdatedCallback ts_callback, void* user_data);

/*!
    \brief Sets EMG streaming options.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] emg_options specified emg options
    \return #TsStatusCode
    \sa TsEmgOptions
*/
TS_API TsStatusCode TS_CALL ts_emg_set_options(TsDeviceHandle* dev, TsEmgOptions emg_options);

/*!
    \brief Starts EMG sensors streaming.

    Update callback should be set before the start, using #ts_emg_set_update_callback.

    \pre #ts_initialize or #ts_initialize_with_path, ts_emg_set_update_callback
    \param[in] dev attached device handler
    \return #TsStatusCode
    \sa TsEmgUpdatedCallback, ts_emg_stop_streaming
*/
TS_API TsStatusCode TS_CALL ts_emg_start_streaming(TsDeviceHandle* dev);

/*!
    \brief Stops EMG sensors streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \return #TsStatusCode
    \sa ts_emg_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_emg_stop_streaming(TsDeviceHandle* dev);

/*!
    \brief Gets EMG sensor options from received data.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[out] sensor_options preallocated EMG sensor options
    \return #TsStatusCode
    \sa TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_options(const TsEmgData emg_data, TsEmgOptions* sensor_options);

/*!
    \brief Gets a number of nodes in EMG sensor.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[out] number_of_nodes number of nodes of EMG sensors
    \return #TsStatusCode
    \sa TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_number_of_nodes(const TsEmgData emg_data, uint8_t* number_of_nodes);

/*!
    \brief Gets an array of node indexes with EMG data.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[out] node_indexes array of node indexes
    \param[in] number_of_nodes size of `node_indexes` array
    \return #TsStatusCode
    \sa TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_node_indexes(const TsEmgData emg_data,
        uint8_t* node_indexes, uint8_t number_of_nodes);

/*!
    \brief Gets a number of channels on node with EMG data.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[in] node_index node index to get number of channels from
    \param[out] number_of_channels number of channels on node with EMG data
    \return #TsStatusCode
    \sa TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_number_of_channels(const TsEmgData emg_data, uint8_t node_index,
        uint64_t* number_of_channels);

/*!
    \brief Gets a size of EMG channel data.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[in] node_index index of required node
    \param[out] size size of channel data
    \return #TsStatusCode
    \sa ts_emg_get_channel_data, TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_channel_data_size(const TsEmgData emg_data, uint8_t node_index,
        uint64_t* size);

/*!
    \brief Gets EMG channel data.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[in] node_index node to get data from
    \param[in] channel_index channel to get data from
    \param[out] channel_data pointer to preallocated block of memory to fill with channel EMG data
    \param[in] channel_data_size size of `channel_data`
    \return #TsStatusCode
    \sa ts_emg_get_channel_data_size, TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_channel_data(const TsEmgData emg_data, uint8_t node_index,
        uint32_t channel_index, int64_t* channel_data, uint64_t channel_data_size);

/*!
    \brief Gets a number of EMG timestamps for a node.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[in] node_index node to get timestamps from
    \param[out] number_of_timestamps number of EMG timestamps
    \return #TsStatusCode
    \sa ts_emg_get_node_timestamps, TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_number_of_node_timestamps(const TsEmgData emg_data, uint8_t node_index,
        uint64_t* number_of_timestamps);

/*!
    \brief Gets EMG timestamps for node.

    Requires #TsEmgData `emg_data` received in #TsEmgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsEmgUpdatedCallback
    \param[in] emg_data data handler received from #TsEmgUpdatedCallback
    \param[in] node_index node to get timestamps from
    \param[out] timestamps pointer to preallocated block of memory
    \param[in] number_of_timestamps size of `timestamps`
    \return #TsStatusCode
    \sa ts_emg_get_number_of_node_timestamps, TsEmgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_emg_get_node_timestamps(const TsEmgData emg_data, uint8_t node_index,
        uint64_t* timestamps, uint64_t number_of_timestamps);

/*!
    \brief Sets PPG data updated callback.

    After a callback was set, streaming can be started with #ts_ppg_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] ts_callback callback with #TsPpgData
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa ts_ppg_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_ppg_set_update_callback(TsDeviceHandle* dev
    , TsPpgUpdatedCallback ts_callback, void* user_data);

/*!
    \brief Sets HRV data updated callback.

    After a callback was set, streaming can be started with #ts_ppg_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] ts_callback callback with #TsHrvData
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa ts_ppg_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_hrv_set_update_callback(TsDeviceHandle* dev
    , TsHrvUpdatedCallback ts_callback, void* user_data);

/*!
    \brief Starts PPG streaming.

    Update callback should be set before start, using #ts_ppg_set_update_callback.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_ppg_set_update_callback
    \param[in] dev attached device handler
    \return #TsStatusCode
    \sa ts_ppg_set_update_callback, ts_ppg_stop_streaming
*/
TS_API TsStatusCode TS_CALL ts_ppg_start_streaming(TsDeviceHandle* dev);

/*!
    \brief Stops PPG streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_ppg_stop_streaming(TsDeviceHandle* dev);

/*!
    \brief Gets number of nodes with PPG data.

    Requires #TsPpgData `ppg_data` received in #TsPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsPpgUpdatedCallback
    \param[in] ppg_data data handler received from #TsPpgUpdatedCallback
    \param[out] number_of_nodes number of nodes with PPG data
    \return #TsStatusCode
    \sa ts_ppg_get_node_indexes, TsPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_get_number_of_nodes(const TsPpgData ppg_data, uint8_t* number_of_nodes);

/*!
    \brief Gets an array of node indexes with PPG data.

    Requires #TsPpgData `ppg_data` received in #TsPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsPpgUpdatedCallback
    \param[in] ppg_data data handler  received from #TsPpgUpdatedCallback
    \param[out] node_indexes preallocated array of node indexes with PPG data
    \param[in] number_of_indexes size of `node_indexes` array
    \return #TsStatusCode
    \sa ts_ppg_get_number_of_nodes, TsPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_get_node_indexes(const TsPpgData ppg_data, uint8_t* node_indexes,
        uint8_t number_of_indexes);

/*!
    \brief Gets heart rate from PPG sensor.

    Requires #TsPpgData `ppg_data` received in #TsPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsPpgUpdatedCallback
    \param[in] ppg_data data handler received from #TsPpgUpdatedCallback
    \param[in] node_index index of node from which to get heart rate
    \param[out] heart_rate heart rate got from PPG processor
    \return #TsStatusCode
    \sa ts_ppg_get_node_indexes, TsPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_get_heart_rate(const TsPpgData ppg_data, uint8_t node_index,
        uint32_t* heart_rate);

/*!
    \brief Checks out if current heart rate from PPG sensor is valid.

    Requires #TsPpgData `ppg_data` received in #TsPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsPpgUpdatedCallback
    \param[in] ppg_data data handler received from #TsPpgUpdatedCallback
    \param[in] node_index index of node to get heart rate valid state from
    \param[out] is_valid heart rate state
    \return #TsStatusCode
    \sa ts_ppg_get_node_indexes, TsPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_is_heart_rate_valid(const TsPpgData ppg_data, uint8_t node_index,
        bool* is_valid);

/*!
    \brief Gets timestamp of data from PPG sensor.

    Requires #TsPpgData `ppg_data` received in #TsPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsPpgUpdatedCallback
    \param[in] ppg_data data handler received from #TsPpgUpdatedCallback
    \param[in] node_index index of node to get timestamp from
    \param[out] timestamp time point of data capturing in milliseconds
    \return #TsStatusCode
    \sa ts_ppg_get_node_indexes, TsPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_get_timestamp(const TsPpgData ppg_data, uint8_t node_index,
        uint64_t* timestamp);

/*!
    \brief Gets processed HRV data from PPG sensor.

    Requires #TsHrvData `hrv_data` received in #TsHrvUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsPpgUpdatedCallback
    \param[in] hrv_data data handler received from #TsHrvUpdatedCallback
    \param[out] hrv data structure that handles processed HRV
    \return #TsStatusCode
    \sa TsHrvUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_hrv_get_data(const TsHrvData hrv_data, TsHrv* hrv);

/*!
    \brief Sets raw PPG data updated callback.

    After a callback was set, streaming can be started with #ts_ppg_raw_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] ts_callback callback with #TsRawPpgData
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa ts_ppg_raw_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_set_update_callback(TsDeviceHandle* dev,
        TsRawPpgUpdatedCallback ts_callback, void* user_data);

/*!
    \brief Starts raw PPG streaming.

    Update callback should be set before start, using #ts_ppg_raw_set_update_callback.

    \pre #ts_initialize or #ts_initialize_with_path, ts_ppg_raw_set_update_callback
    \param[in] dev attached device handler
    \return #TsStatusCode
    \sa ts_ppg_raw_set_update_callback, ts_ppg_raw_stop_streaming
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_start_streaming(TsDeviceHandle* dev);

/*!
    \brief Stops raw PPG streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to attached device
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_stop_streaming(TsDeviceHandle* dev);

/*!
    \brief  Calibrates PPG processor.

    The calibration procedure is capturing interval of the raw data during 3 seconds.
    The captured interval will be used in calculation of all ppg parameters.
    By default, calibration procedure starts on starting PPG processor.
    In case on bad start, the calibration procedure might be restarted using this function.


    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_ppg_calibrate(TsDeviceHandle* dev);

/*!
    \brief Gets number of nodes with raw PPG data.

    Requires #TsRawPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsRawPpgUpdatedCallback
    \param[in] raw_ppg_data data handler received from #TsRawPpgUpdatedCallback
    \param[out] number_of_nodes number of nodes with raw PPG data
    \return #TsStatusCode
    \sa ts_ppg_raw_get_node_indexes, TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_number_of_nodes(const TsRawPpgData raw_ppg_data, uint8_t* number_of_nodes);

/*!
    \brief Gets array of node indexes with raw PPG data.

    Requires #TsRawPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsRawPpgUpdatedCallback
    \param[in] raw_ppg_data data handler received from #TsRawPpgUpdatedCallback
    \param[out] node_indexes array of node indexes
    \param[in] number_of_indexes size of `node_indexes` array
    \return #TsStatusCode
    \sa ts_ppg_raw_get_number_of_nodes, TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_node_indexes(const TsRawPpgData raw_ppg_data,
        uint8_t* node_indexes, uint8_t number_of_indexes);

/*!
    \brief Gets raw PPG data size.

    Requires #TsRawPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsRawPpgUpdatedCallback
    \param[in] raw_ppg_data data handler received from #TsRawPpgUpdatedCallback
    \param[in] node_index index of node with PPG data
    \param[out] size size of data
    \return #TsStatusCode
    \sa TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_data_size(const TsRawPpgData raw_ppg_data, uint8_t node_index,
        uint64_t* size);

/*!
    \brief Gets raw infrared data from PPG sensor.

    Requires #TsRawPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback and
    `size` received in #ts_ppg_raw_get_data_size.

    \pre #ts_initialize or #ts_initialize_with_path, #TsRawPpgUpdatedCallback
    \param[in] raw_ppg_data data handler received from #TsRawPpgUpdatedCallback
    \param[in] node_index index of node to get infrared data from
    \param[out] infrared_data preallocated memory for raw infrared data received from PPG sensor
    \param[in] size size of `infrared_data`
    \return #TsStatusCode
    \sa ts_ppg_raw_get_data_size, TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_infrared_data(const TsRawPpgData raw_ppg_data, uint8_t node_index,
        uint64_t* infrared_data, uint64_t size);

/*!
    \brief Gets raw red data from PPG sensor.

    Requires #TsRawPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback and
    `size` received in #ts_ppg_raw_get_data_size.

    \pre #ts_initialize or #ts_initialize_with_path, #TsRawPpgUpdatedCallback
    \param[in] raw_ppg_data data handler received from #TsRawPpgUpdatedCallback
    \param[in] node_index index of node to get red data from
    \param[out] red_data preallocated memory for raw red data received from PPG sensor
    \param[in] size size of `red_data`
    \return #TsStatusCode
    \sa ts_ppg_raw_get_data_size, TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_red_data(const TsRawPpgData raw_ppg_data, uint8_t node_index,
        uint64_t* red_data, uint64_t size);

/*!
    \brief Gets raw blue data from PPG sensor.

    Requires #TsRawPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback and
    `size` received in #ts_ppg_raw_get_data_size.

    \pre #ts_initialize or #ts_initialize_with_path, #TsRawPpgUpdatedCallback
    \param[in] raw_ppg_data data hanler received from #TsRawPpgUpdatedCallback
    \param[in] node_index index of node to get blue_data from
    \param[out] blue_data preallocated memory for raw blue data received from PPG sensor
    \param[in] size size of `blue_data`
    \return #TsStatusCode
    \sa ts_ppg_raw_get_data_size, TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_blue_data(const TsRawPpgData raw_ppg_data, uint8_t node_index,
        uint64_t* blue_data, uint64_t size);

/*!
    \brief Gets raw green data from PPG sensor.

    Requires #TsRawPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback and
    `size` received in #ts_ppg_raw_get_data_size.

    \pre #ts_initialize or #ts_initialize_with_path, #TsRawPpgUpdatedCallback
    \param[in] raw_ppg_data data handler received from #TsRawPpgUpdatedCallback
    \param[in] node_index index of node to get green_data from
    \param[out] green_data preallocated memory for raw green data received from PPG sensor
    \param[in] size size of `green_data`
    \return #TsStatusCode
    \sa ts_ppg_raw_get_data_size, TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_green_data(const TsRawPpgData raw_ppg_data, uint8_t node_index,
        uint64_t* green_data, uint64_t size);

/*!
    \brief Gets raw PPG data timestamp of node.

    Requires #TsPpgData `raw_ppg_data` received in #TsRawPpgUpdatedCallback.

    \pre #ts_initialize or #ts_initialize_with_path, #TsPpgUpdatedCallback
    \param[in] raw_ppg_data data handler received from #TsRawPpgUpdatedCallback
    \param[in] node_index index of node to get timestamp from
    \param[out] timestamp time point of raw data capturing in milliseconds
    \return #TsStatusCode
    \sa TsRawPpgUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_ppg_raw_get_timestamp(const TsRawPpgData raw_ppg_data, uint8_t node_index,
        uint64_t* timestamp);

/*!
    \brief Sets BIA data updated callback.

    After a callback was set, streaming can be started with #ts_bia_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] ts_callback callback with #TsBiaData
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa ts_bia_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_bia_set_update_callback(TsDeviceHandle* dev, 
    TsBiaUpdatedCallback ts_callback, void* user_data);

/*!
    \brief Sets BIA streaming config.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] config streaming parameters
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_bia_set_streaming_config(TsDeviceHandle* dev,
    const TsBiaConfig* config);

/*!
    \brief Starts BIA data streaming.

    Update callback should be set before start, using #ts_bia_set_update_callback.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_bia_set_update_callback
    \param[in] dev attached device handler
    \return #TsStatusCode
    \sa ts_bia_set_update_callback
*/
TS_API TsStatusCode TS_CALL ts_bia_start_streaming(TsDeviceHandle* dev);

/*!
    \brief Stops BIA data streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_bia_stop_streaming(TsDeviceHandle* dev);

/*!
    \brief Gets a number of BIA channels for node.

    \pre #ts_initialize or #ts_initialize_with_path, #TsBiaUpdatedCallback
    \param[in] bia_data BIA data handler
    \param[out] number_of_channels number of channels with BIA data
    \return #TsStatusCode
    \sa ts_bia_get_node_channel_indexes, TsBiaUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_bia_get_number_of_channels(const TsBiaData bia_data,
        uint64_t* number_of_channels);

/*!
    \brief Gets BIA channels indexes.

    \pre #ts_initialize or #ts_initialize_with_path, #TsBiaUpdatedCallback
    \param[in] bia_data handler to BIA data
    \param[out] channel_indexes preallocated array of indexes
    \param[in] size size of `channel_indexes`
    \return #TsStatusCode
    \sa ts_bia_get_number_of_channels, TsBiaUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_bia_get_channels_indexes(const TsBiaData bia_data,
        uint32_t* channel_indexes, uint64_t size);

/*!
    \brief Gets BIA channel number of frequencies.

    \pre #ts_initialize or #ts_initialize_with_path, #TsBiaUpdatedCallback
    \param[in] bia_data BIA data handler
    \param[in] channel_index index of channel to get number of frequencies
    \param[out] number_of_frequencies number of frequencies
    \return #TsStatusCode
    \sa ts_bia_get_channel_frequencies, TsBiaUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_bia_get_channel_number_of_frequencies(const TsBiaData bia_data,
        uint32_t channel_index, uint64_t* number_of_frequencies);

/*!
    \brief Gets BIA channel frequencies values for channel.

    \pre #ts_initialize or #ts_initialize_with_path, #TsBiaUpdatedCallback
    \param[in] bia_data BIA data handler
    \param[in] channel_index index of channel to get frequencies
    \param[out] frequencies Preallocated frequency values array
    \param[in] size size of `frequencies`
    \return #TsStatusCode
    \sa ts_bia_get_channel_number_of_frequencies, TsBiaUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_bia_get_channel_frequencies(const TsBiaData bia_data,
        uint32_t channel_index, uint32_t* frequencies, uint64_t size);

/*!
    \brief Gets BIA channel frequency complex number value.

    \pre #ts_initialize or #ts_initialize_with_path, #TsBiaUpdatedCallback
    \param[in] bia_data BIA data handler
    \param[in] channel_index index of channel to get data
    \param[in] frequency_value frequency to get data from
    \param[out] complex_value complex value of frequency
    \return #TsStatusCode
    \sa TsBiaUpdatedCallback
*/
TS_API TsStatusCode TS_CALL ts_bia_get_channel_frequency_complex_value(const TsBiaData bia_data,
    uint32_t channel_index, uint32_t frequency_value,
        TsComplex* complex_value);

/*!
    \brief Sets Current feddback data updated callback.

    After a callback was set, streaming can be started with #ts_current_feedback_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \param[in] ts_callback callback with #TsCurrentFeedbackData
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa ts_current_feedback_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_set_update_callback(TsDeviceHandle* dev,
    TsCurrentFeedbackUpdatedCallback ts_callback, void* user_data);

/*!
    \brief Starts current feedback data streaming.

    Update callback should be set before start, using #ts_current_feedback_set_update_callback.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_current_feedback_set_update_callback
    \param[in] dev attached device handler
    \return #TsStatusCode
    \sa ts_current_feedback_set_update_callback
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_start_streaming(TsDeviceHandle* dev);

/*!
    \brief Stops current feedback data streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev attached device handler
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_stop_streaming(TsDeviceHandle* dev);

/*!
    \brief Get number of connected nodes.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] data handle to current feedback data
    \param[out] number_of_nodes number of available nodes
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_get_number_of_nodes(TsCurrentFeedbackData data,
    uint64_t* number_of_nodes);

/*!
    \brief Get connected nodes indexes.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] data handle to current feedback data
    \param[out] nodes_indexes pointer to preallocated array to handle nodes indexes
    \param[in] number_of_nodes number of available nodes
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_get_nodes_indexes(TsCurrentFeedbackData data,
    uint8_t* nodes_indexes, uint64_t number_of_nodes);

/*!
    \brief Get number of available channels for specified node.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] data handle to current feedback data
    \param[in] node_index index of desired node
    \param[out] number_of_channels number of available nodes
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_get_number_of_node_channels(TsCurrentFeedbackData data,
    uint8_t node_index, uint64_t* number_of_channels);

/*!
    \brief Get indexes of available channels for specified node.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] data handle to current feedback data
    \param[in] node_index index of desired node
    \param[out] channels_indexes pointer to preallocated array to handle channels indexes
    \param[in] number_of_channels number of available nodes
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_get_channels_indexes(TsCurrentFeedbackData data,
    uint8_t node_index, uint32_t* channels_indexes, uint64_t number_of_channels);

/*!
    \brief Get indexes of available channels for specified node.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] data handle to current feedback data
    \param[in] node_index index of desired node
    \param[in] channel_index index of desired channel
    \param[out] channel_value current value of channel
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_current_feedback_get_channel_value(TsCurrentFeedbackData data,
    uint8_t node_index, uint32_t channel_index, uint32_t* channel_value);

/**@}*/

TS_EXTERN_C_END
