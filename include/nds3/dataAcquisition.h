#ifndef NDSDATAACQUISITION_H
#define NDSDATAACQUISITION_H

/**
 * @file dataAcquisition.h
 * @brief Defines the DataAcquisition node, which provides basic services for data
 *        acquisition.
 *
 * Include nds3.h instead of this one, since nds3.h takes care of including all the
 * necessary header files (including this one).
 */

#include "definitions.h"
#include "node.h"

namespace nds
{

/**
 * This is a node that supplies a data acquisition PV and few control
 * PV that specifies how the acquisition should be performed.
 *
 * It also provides a state machine that allows to start/stop the acquisition.
 *
 * The user of a DataAcquisition class must declare few delegate functions that
 *  specify the actions to perform when the acquisition node's state changes.
 *
 * In particular, the transition from the state off to running should launch
 *  the data acquisition thread which pushes the acquired data via pushData(),
 *  while the transition from running to on should stop the data acquisition thread.
 *
 */
template <typename T>
class NDS3_API DataAcquisition: public Node
{
public:
    DataAcquisition();

    DataAcquisition(const DataAcquisition<T>& right);

    DataAcquisition& operator=(const DataAcquisition<T>& right);

    /**
     * @brief Constructs the data acquisition node.
     *
     */
    DataAcquisition(const std::string& name,               ///< The node's name
                    recordType_t recordType,               ///< The acquisition PV type
                    size_t maxElements,                    ///< Maximum size of the acquired array. Set to 1 for scalar values
                    stateChange_t switchOnFunction,        ///< Delegate function that performs the actions to switch the node on
                    stateChange_t switchOffFunction,       ///< Delegate function that performs the actions to switch the node off
                    stateChange_t startFunction,           ///< Delegate function that performs the actions to start the acquisition (usually launches the acquisition thread)
                    stateChange_t stopFunction,            ///< Delegate function that performs the actions to stop the acquisition (usually stops the acquisition thread)
                    stateChange_t recoverFunction,         ///< Delegate function to execute to recover from an error state
                    allowChange_t allowStateChangeFunction ///< Delegate function that can deny a state change. Usually just returns true
                    );

    /**
     * @ingroup datareadwrite
     * @brief Push acquired data to the control system.
     *
     * Usually your device implementation will call this function from the
     *  data acquisition thread in order to push the acquired data.
     *
     * @param timestamp the timestamp for the data
     * @param data      the data to push to the control system
     */
    void pushData(const timespec& timestamp, const T& data);

    /**
     * @brief Retrieve the desidered acquisition frequency, in Hertz.
     *
     * @return the acquisition frequency in Hertz
     */
    double getFrequencyHz();

    /**
     * @brief Retrieve the desidered duration of the acquisition, in seconds
     *
     * @return the desidered duration of the acquisition, in seconds
     */
    double getDurationSeconds();

    /**
     * @brief Retrieve the maximum number of elements that can be stored in the
     *        pushed array. This number is set in the DataAcquisition constructor.
     *
     * @return the maximum number of elements that can be stored in the pushed array
     */
    size_t getMaxElements();

    /**
     * @brief Retrieve the desidered decimation value.
     *
     * @return the decimation value
     */
    size_t getDecimation();

    /**
     * @ingroup timing
     * @brief Returns the timestamp at the moment of the start of the acquisition.
     *
     * This value is set by the state machine when the state switches to running.
     * If a timing plugin is active then the timestamp is taken from the plugin.
     *
     * @return the time when the acquisition started.
     */
    timespec getStartTimestamp();
};

}
#endif // NDSDATAACQUISITION_H

