/*************************************************************************
	> File Name: thread.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月14日 星期二 19时58分18秒
    > Function: 
 ************************************************************************/

Thread::Thread()
{
    thread_ID_ = -1;
    is_exit_ = false;
    is_detach_ = true;
}

ReturnStatus Thread::Run()
{
    int rec = pthread_create(&thread_ID_,nullptr,StartFunctionOfThread,this);
    if(0 != rec)
    {
        std::cout << "pthread_creat error" << std::endl;
        return ReturnStatus(-1,rec);        
    }

    if(is_detach_)
    {
        rec = pthread_detach(thread_ID_);
        if(0 != rec)
        {
            std::cout << "pthread_detach error" << std::endl;
            return ReturnStatus(-1.rec);
        }
    }
    
    return ReturnStatus(0,0);
}

void Thread::ReceiveTask(Task *task)
{
    message_.PostMessage(task);
}

void *StartFunctionOfThread(void *p)
{
    while(p->is_exit_ == false)
    {
        Task *task;
        ReturnStatus return_status = (p->message_).GetMessage(task,true);
        if(-1 == return_status.return_value())
        {
            std::cout << "GetMessage error" << std::endl;
            throw "GetMessage error";
        }
        task->TaskFunction();
        ThreadPoolManagerment::GetInstance()->RecycleTask(task);
    }
}

void Thread::Stop()
{
    is_exit_ = true;
}
