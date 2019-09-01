#ifndef PROCEDUREBUILDER_H
#define PROCEDUREBUILDER_H

#include "Procedure.h"

/**
 * A Procedure is a sequence of functions that will be executed in an given order
 * each one separated from the other by a fixed or variable amount of time.
 * The sequence can be executed repeatedly or just one time
 *
 * Four types of functions can be composed to form a Procedure:
 * - two can take an argument that can be used as a state holder
 * - two return the amount of time that separate them from the next one
 *
 * Usage example:
 *
 * SomeType stateHolder;
 * void makeSomething();
 * void makeSomethingUsingState(SomeType state);
 * uint32_t makeSomethingReturnInterval();
 * uint32_t makeSomethingReturnIntervalUsingState(SomeType state);
 *
 * Procedure &procedure = ProcedureBuilder::begin(makeSomething, MsToTaskTime(1000))     // (1)
 *        .then(makeSomethingUsingState, stateHolder, MsToTaskTime(2000))                // (2)
 *        .then(makeSomethingReturnInterval)                                             // (3)
 *        .then(makeSomethingReturnIntervalUsingState, stateHolder)                      // (4)
 *        .thenRepeat();                                                                 // (5)
 *
 * taskManager.StartTask(&procedure);
 *
 * Will produce a procedure that:
 * (1) begin executing makeSomething() and then waiting for one second
 * (2) then executes makeSomethingUsingState(stateHolder) and waits for two seconds
 * (3) then executes makeSomethingReturnInterval() and waits for time interval returned by the function
 * (4) then executes makeSomethingReturnIntervalUsingState(stateHolder)
 *     and waits for time interval returned by the function
 * (5) then repeat the sequence. Use done() to execute the sequence just one time
 *
 */
class ProcedureBuilder
{
public:
    static ProcedureBuilder begin(void (*callback)(), uint32_t nextInterval);
    static ProcedureBuilder begin(uint32_t (*callbackReturningInterval)());
    template<typename T> static ProcedureBuilder begin(
            void (*callbackWithState)(T*), T *state, uint32_t nextInterval);
    template<typename T>
    static ProcedureBuilder begin(
            uint32_t (*callbackReturningIntervalWithState)(T*), T *state);
    ProcedureBuilder& then(void (*callback)(), uint32_t nextInterval);
    ProcedureBuilder& then(uint32_t (*callbackReturningInterval)());
    template<typename T>
    ProcedureBuilder& then(void (*callbackWithState)(T*), T *state,
            uint32_t nextInterval);
    template<typename T>
    ProcedureBuilder& then(uint32_t (*callbackReturningIntervalWithState)(T*),
            T *state);
    Procedure& done();
    Procedure& thenRepeat();
private:
    ProcedureBuilder(Procedure &instance);
    Procedure &instance;
};

inline ProcedureBuilder::ProcedureBuilder(Procedure &instance) :
        instance(instance)
{

}

inline ProcedureBuilder ProcedureBuilder::begin(void (*callback)(),
        uint32_t nextInterval)
{
    ProcedureNode *pTaskNode = new Callback(callback, nextInterval);
    Procedure *pInstance = new Procedure(pTaskNode);
    ProcedureBuilder builder { *pInstance };
    return builder;
}

inline ProcedureBuilder ProcedureBuilder::begin(
        uint32_t (*callbackReturningInterval)())
{

    ProcedureNode *pTaskNode = new CallbackReturningInterval(
            callbackReturningInterval);
    Procedure *pInstance = new Procedure(pTaskNode);
    ProcedureBuilder builder { *pInstance };
    return builder;
}

template<typename T>
inline ProcedureBuilder ProcedureBuilder::begin(void (*callbackWithState)(T*),
        T *state, uint32_t nextInterval)
{

    ProcedureNode *pTaskNode = new CallbackWithState(
            (void (*)(void*)) callbackWithState, nextInterval, (void*) state);
    Procedure *pInstance = new Procedure(pTaskNode);
    ProcedureBuilder builder {*pInstance};
    return builder;
}

template<typename T>
inline ProcedureBuilder ProcedureBuilder::begin(
        uint32_t (*callbackReturningIntervalWithState)(T*), T *state)
{

    ProcedureNode *pTaskNode = new CallbackWithStateReturningInterval(
            (uint32_t (*)(void*)) callbackReturningIntervalWithState, (void*) state);
    Procedure *pInstance = new Procedure(pTaskNode);
    ProcedureBuilder builder {*pInstance};
    return builder;
}

inline ProcedureBuilder& ProcedureBuilder::then(void (*callback)(),
        uint32_t nextInterval)
{

    instance.pLastNode->pNext = new Callback(callback, nextInterval);
    instance.pLastNode = instance.pLastNode->pNext;

    return *this;
}

inline ProcedureBuilder& ProcedureBuilder::then(
        uint32_t (*callbackReturningInterval)())
{

    instance.pLastNode->pNext = new CallbackReturningInterval(
            callbackReturningInterval);
    instance.pLastNode = instance.pLastNode->pNext;

    return *this;
}

template<typename T>
inline ProcedureBuilder& ProcedureBuilder::then(void (*callbackWithState)(T*),
        T *state, uint32_t nextInterval)
{

    instance.pLastNode->pNext = new CallbackWithState(
            (void (*)(void*)) callbackWithState, nextInterval, state);
    instance.pLastNode = instance.pLastNode->pNext;

    return *this;
}

template<typename T>
inline ProcedureBuilder& ProcedureBuilder::then(
        uint32_t (*callbackReturningIntervalWithState)(T*), T *state)
{

    instance.pLastNode->pNext = new CallbackWithStateReturningInterval(
            (uint32_t (*)(void*)) callbackReturningIntervalWithState, state);
    instance.pLastNode = instance.pLastNode->pNext;

    return *this;
}

inline Procedure& ProcedureBuilder::done()
{
    instance.repeat = false;
    return instance;
}

inline Procedure& ProcedureBuilder::thenRepeat()
{
    instance.repeat = true;
    return instance;
}

#endif
