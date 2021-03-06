
#include <game/dbsrv/WriterThreadPool.h>

WriterThreadPool::WriterThreadPool():
	threadnum_(0)
{
}

WriterThreadPool::~WriterThreadPool()
{
	for (int i = 0; i < threadnum_; i++)
	{
		delete threads_[i];
	}
}

void WriterThreadPool::start(int threadnum)
{
	threadnum_ = threadnum;
	threads_.resize(threadnum);
	for (int i = 0; i < threadnum; i++)
	{
		threads_[i] = new WriterThread(i + 1);
	}

	for (int i = 0; i < threadnum_; i++)
	{
		threads_[i]->start();
	}
}

void WriterThreadPool::stop()
{
	for (int i = 0; i < threadnum_; i++)
	{
		threads_[i]->stop();
	}
}

void WriterThreadPool::push(WriterThreadParam& param)
{
	static int nextThreadId = 0;
	nextThreadId++;
	if (nextThreadId >= threadnum_)
	{
		nextThreadId = 0;
	}

	threads_[nextThreadId]->push(param);
}

void WriterThreadPool::push(int threadId, WriterThreadParam& param)
{
	if (threadId >= threadnum_ || threadId < 0)
	{
		LOG_ERROR << "WriterThreadPool::push threadid error, threadid: " << threadId;
		push(param);
		return;
	}

	threads_[threadId]->push(param);
}

void WriterThreadPool::ping()
{
	WriterThreadParam param;
	param.Type = WRITERTHREAD_PING;

	for (int i = 0; i < threadnum_; i++)
	{
		threads_[i]->push(param);
	}
}

#include <sstream>
std::string WriterThreadPool::getQueueInfo()
{
	std::stringstream buf;
	buf << "[";
	for (int i = 0; i < threadnum_; i++)
	{
		buf << "{";
		buf << i;
		buf << ":";
		buf << threads_[i]->getQueueSize();
		buf << "}";
	}
	buf << "]";
	return buf.str();
}

int WriterThreadPool::getThreadNum()
{
	return threadnum_;
}
