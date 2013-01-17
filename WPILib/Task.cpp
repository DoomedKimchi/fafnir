/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Task.h"

#include "WPIErrors.h"
#include <errnoLib.h>
#include <string.h>
#include <taskLib.h>
#include <usrLib.h>

const UINT32 Task::kDefaultPriority;
const INT32 Task::kInvalidTaskID;

/**
 * Create but don't launch a task.
 * @param name The name of the task.  "FRC" will be prepended to the task name.
 * @param function The address of the function to run as the new task.
 * @param priority The VxWorks priority for the task.
 * @param stackSize The size of the stack for the task
 */
Task::Task(const char* name, FUNCPTR function, INT32 priority, UINT32 stackSize)
{
	m_taskID = kInvalidTaskID;
	m_function = function;
	m_priority = priority;
	m_stackSize = stackSize;
	m_taskName = new char[strlen(name) + 5];
	strcpy(m_taskName, "FRC_");
	strcpy(m_taskName+4, name);
}

Task::~Task()
{
	if (m_taskID != kInvalidTaskID) Stop();
	delete [] m_taskName;
	m_taskName = NULL;
}

/**
 * Starts this task.
 * If it is already running or unable to start, it fails and returns false.
 */
bool Task::Start(UINT32 arg0, UINT32 arg1, UINT32 arg2, UINT32 arg3, UINT32 arg4, 
		UINT32 arg5, UINT32 arg6, UINT32 arg7, UINT32 arg8, UINT32 arg9)
{
	m_taskID = taskSpawn(m_taskName,
						m_priority,
						VX_FP_TASK,							// options
						m_stackSize,						// stack size
						m_function,							// function to start
						arg0, arg1, arg2, arg3, arg4,	// parameter 1 - pointer to this class
						arg5, arg6, arg7, arg8, arg9);// additional unused parameters
	bool ok = HandleError(m_taskID);
	if (!ok) m_taskID = kInvalidTaskID;
	return ok;
}

/**
 * Restarts a running task.
 * If the task isn't started, it starts it.
 * @return false if the task is running and we are unable to kill the previous instance
 */
bool Task::Restart()
{
	return HandleError(taskRestart(m_taskID));
}

/**
 * Kills the running task.
 * @returns true on success false if the task doesn't exist or we are unable to kill it.
 */
bool Task::Stop()
{
	bool ok = true;
	if (Verify())
	{
		ok = HandleError(taskDelete(m_taskID));
	}
	m_taskID = kInvalidTaskID;
	return ok;
}

/**
 * Returns true if the task is ready to execute (i.e. not suspended, delayed, or blocked).
 * @return true if ready, false if not ready.
 */
bool Task::IsReady()
{
	return taskIsReady(m_taskID);
}

/**
 * Returns true if the task was explicitly suspended by calling Suspend()
 * @return true if suspended, false if not suspended.
 */
bool Task::IsSuspended()
{
	return taskIsSuspended(m_taskID);
}

/**
 * Pauses a running task.
 * Returns true on success, false if unable to pause or the task isn't running.
 */
bool Task::Suspend()
{
	return HandleError(taskSuspend(m_taskID));
}

/**
 * Resumes a paused task.
 * Returns true on success, false if unable to resume or if the task isn't running/paused.
 */
bool Task::Resume()
{
	return HandleError(taskResume(m_taskID));
}

/**
 * Verifies a task still exists.
 * @returns true on success.
 */
bool Task::Verify()
{
	return taskIdVerify(m_taskID) == OK;
}

/**
 * Gets the priority of a task.
 * @returns task priority or 0 if an error occured
 */
INT32 Task::GetPriority()
{
	if (HandleError(taskPriorityGet(m_taskID, &m_priority)))
		return m_priority;
	else
		return 0;
}

/**
 * This routine changes a task's priority to a specified priority.
 * Priorities range from 0, the highest priority, to 255, the lowest priority.
 * Default task priority is 100.
 * @param priority The priority the task should run at.
 * @returns true on success.
 */
bool Task::SetPriority(INT32 priority)
{
	m_priority = priority;
	return HandleError(taskPrioritySet(m_taskID, m_priority));
}

/**
 * Returns the name of the task.
 * @returns Pointer to the name of the task or NULL if not allocated
 */
const char* Task::GetName()
{
	return m_taskName;
}

/**
 * Get the ID of a task
 * @returns Task ID of this task.  Task::kInvalidTaskID (-1) if the task has not been started or has already exited.
 */
INT32 Task::GetID()
{
	if (Verify())
		return m_taskID;
	return kInvalidTaskID;
}

/**
 * Handles errors generated by task related code.
 */
bool Task::HandleError(STATUS results)
{
	if (results != ERROR) return true;
	switch(errnoGet())
	{
	case S_objLib_OBJ_ID_ERROR:
		wpi_setWPIErrorWithContext(TaskIDError, m_taskName);
		break;
		
	case S_objLib_OBJ_DELETED:
		wpi_setWPIErrorWithContext(TaskDeletedError, m_taskName);
		break;
		
	case S_taskLib_ILLEGAL_OPTIONS:
		wpi_setWPIErrorWithContext(TaskOptionsError, m_taskName);
		break;
		
	case S_memLib_NOT_ENOUGH_MEMORY:
		wpi_setWPIErrorWithContext(TaskMemoryError, m_taskName);
		break;
		
	case S_taskLib_ILLEGAL_PRIORITY:
		wpi_setWPIErrorWithContext(TaskPriorityError, m_taskName);
		break;

	default:
		printErrno(errnoGet());
		wpi_setWPIErrorWithContext(TaskError, m_taskName);
	}
	return false;
}
