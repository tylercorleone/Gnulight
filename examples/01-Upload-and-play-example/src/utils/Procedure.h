#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "stdint.h"
#include "stddef.h"
#include "Task.h"

/**
 * This file contains the definition of Procedure and ProcedureNodes
 * classes. They are not intended to be used directly.
 * For usage see ProcedureBuilder.h
 */

class ProcedureNode
{
    friend class Procedure;
    friend class ProcedureBuilder;
private:
    virtual void execute() = 0;
    virtual uint32_t getNextInterval() = 0;
    ProcedureNode *pNext = nullptr;
public:
    virtual ~ProcedureNode(){}
};

class Callback: public ProcedureNode
{
    friend class Procedure;
    friend class ProcedureBuilder;
private:
    Callback(void (*function)(), uint32_t nextInterval);
    void execute() override;
    uint32_t getNextInterval() override;
    void (*function)();
    uint32_t nextInterval;
};

class CallbackReturningInterval: public ProcedureNode
{
    friend class Procedure;
    friend class ProcedureBuilder;
private:
    CallbackReturningInterval(uint32_t (*callback)());
    void execute() override;
    uint32_t getNextInterval() override;
    uint32_t (*functionReturningInterval)();
    uint32_t nextInterval = -1;
};

class CallbackWithState: public ProcedureNode
{
    friend class Procedure;
    friend class ProcedureBuilder;
private:
    CallbackWithState(void (*callback)(void*), uint32_t nextInterval,
            void *state);
    void execute() override;
    uint32_t getNextInterval() override;
    void (*functionTakingState)(void*);
    uint32_t nextInterval;
    void *state;
};

class CallbackWithStateReturningInterval: public ProcedureNode
{
    friend class Procedure;
    friend class ProcedureBuilder;
private:
    CallbackWithStateReturningInterval(uint32_t (*callback)(void*),
            void *state);
    void execute() override;
    uint32_t getNextInterval() override;
    uint32_t (*functionTakingStateReturningInterval)(void*);
    uint32_t nextInterval = -1;
    void *state;
};

class Procedure: public Task
{
    friend class ProcedureBuilder;
private:
    Procedure(ProcedureNode *pTaskNode);
    Procedure(const Procedure&) = delete;
    Procedure& operator=(const Procedure&) = delete;
    bool OnStart() override;
    void OnUpdate(uint32_t taskDeltaTime) override;

    ProcedureNode *pFirstNode;
    ProcedureNode *pLastNode;
    ProcedureNode *pNodeToRun = nullptr;
    bool repeat = false;
    bool sequenceCompleted = false;
public:
    virtual ~Procedure();
};

#include "ProcedureBuilder.h"

/*
 * Implementation
 */

inline Procedure::~Procedure()
{
    ProcedureNode *pIterate;
    pIterate = pFirstNode;
    while (pIterate != nullptr)
    {
        ProcedureNode *pNext = pIterate->pNext;
        delete pIterate;
        pIterate = pNext;
    }
}

inline Procedure::Procedure(ProcedureNode *pTaskNode) :
        Task(-1)
{
    pFirstNode = pLastNode = pTaskNode;
}

inline bool Procedure::OnStart()
{
    pNodeToRun = pFirstNode;
    sequenceCompleted = false;
    setRemainingTime(0);
    return true;
}

inline void Procedure::OnUpdate(uint32_t taskDeltaTime)
{
    if (sequenceCompleted && !repeat)
    {
        Suspend();
        return;
    }

    pNodeToRun->execute();
    setTimeInterval(pNodeToRun->getNextInterval());

    if (pNodeToRun->pNext != nullptr)
    {
        pNodeToRun = pNodeToRun->pNext;
    }
    else
    {

        /*
         * this is the last node
         */
        if (repeat)
        {
            pNodeToRun = pFirstNode;
        }
        else
        {
            sequenceCompleted = true;
            Suspend();
        }
    }
}

inline Callback::Callback(void (*function)(), uint32_t nextInterval) :
        function(function), nextInterval(nextInterval)
{

}

inline void Callback::execute()
{
    function();
}

inline uint32_t Callback::getNextInterval()
{
    return nextInterval;
}

inline CallbackReturningInterval::CallbackReturningInterval(
        uint32_t (*functionReturningInterval)()) :
        functionReturningInterval(functionReturningInterval)
{

}

inline void CallbackReturningInterval::execute()
{
    nextInterval = functionReturningInterval();
}

inline uint32_t CallbackReturningInterval::getNextInterval()
{
    return nextInterval;
}

inline CallbackWithState::CallbackWithState(void (*functionTakingState)(void*),
        uint32_t nextInterval, void *state) :
        functionTakingState(functionTakingState), nextInterval(nextInterval), state(
                state)
{

}

inline void CallbackWithState::execute()
{
    functionTakingState(state);
}

inline uint32_t CallbackWithState::getNextInterval()
{
    return nextInterval;
}

inline CallbackWithStateReturningInterval::CallbackWithStateReturningInterval(
        uint32_t (*functionTakingStateReturningInterval)(void*), void *state) :
        functionTakingStateReturningInterval(
                functionTakingStateReturningInterval), state(state)
{

}

inline void CallbackWithStateReturningInterval::execute()
{
    nextInterval = functionTakingStateReturningInterval(state);
}

inline uint32_t CallbackWithStateReturningInterval::getNextInterval()
{
    return nextInterval;
}

#endif
