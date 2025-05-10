#pragma once

#include <functional>
#include <future>
#include <memory>
#include <thread>

template<typename T>
class JunuoAsyncCall
{
public:
	static JunuoAsyncCall<T>& post(std::function<T()> task)
	{
		auto self = new JunuoAsyncCall<T>;
		self->m_task = task;
		return *self;
	}

	JunuoAsyncCall<T>& then(std::function<void(T)> nextTask)
	{
		m_nextTask = nextTask;
		return *this;
	}

	void catch_(std::function<void()> catchTask)
	{
		m_catchTask = catchTask;
		asyncCall();
	}

protected:
	JunuoAsyncCall() = default;
	void asyncCall()
	{
		std::thread([this]()
			{
				std::unique_ptr<JunuoAsyncCall<T>> self(this);
				try
				{
					if (!m_task)
						return;
					T ret = m_task();
					if (m_nextTask)
						m_nextTask(ret);
				}
				catch (...)
				{
					if (m_catchTask)
						m_catchTask();
				}
			}).detach();
	}

private:
	std::function<T()> m_task = nullptr;
	std::function<void(T)> m_nextTask = nullptr;
	std::function<void()> m_catchTask = nullptr;
};

// 特化void版本
template<>
class JunuoAsyncCall<void>
{
public:
	static JunuoAsyncCall<void>& post(std::function<void()> task)
	{
		auto self = new JunuoAsyncCall<void>;
		self->m_task = task;
		return *self;
	}

	JunuoAsyncCall<void>& then(std::function<void()> nextTask)
	{
		m_nextTask = nextTask;
		return *this;
	}

	void catch_(std::function<void()> catchTask)
	{
		m_catchTask = catchTask;
		asyncCall();
	}

protected:
	JunuoAsyncCall() = default;
	void asyncCall()
	{
		std::thread([this]()
			{
				std::unique_ptr<JunuoAsyncCall<void>> self(this);
				try
				{
					if (!m_task)
						return;
					m_task();
					if (m_nextTask)
						m_nextTask();
				}
				catch (...)
				{
					if (m_catchTask)
						m_catchTask();
				}
			}).detach();
	}

private:
	std::function<void()> m_task = nullptr;
	std::function<void()> m_nextTask = nullptr;
	std::function<void()> m_catchTask = nullptr;
};
