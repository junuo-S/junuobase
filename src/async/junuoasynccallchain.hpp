#pragma once

#include <functional>
#include <future>
#include <memory>
#include <thread>

template<typename T>
class JunuoAsyncCallChain
{
public:
	using Task = std::function<T()>;
	static std::shared_ptr<JunuoAsyncCallChain<T>> post(Task task)
	{
		auto chain = std::make_shared<JunuoAsyncCallChain<T>>();
		chain->m_future = std::async(std::launch::async, [task, chain] { return task();	});
		return chain;
	}

	template<typename NextT>
	std::shared_ptr<JunuoAsyncCallChain<NextT>> then(std::function<NextT(T)> nextTask)
	{
		auto next = std::make_shared<JunuoAsyncCallChain<NextT>>();
		next->m_future = std::async(std::launch::async, [nextTask, next, this] { return nextTask(m_future.get()); });
		return next;
	}

private:
	std::future<T> m_future;
};

// 特化void版本
template<>
class JunuoAsyncCallChain<void>
{
public:
	using Task = std::function<void()>;
	static std::shared_ptr<JunuoAsyncCallChain<void>> post(Task task)
	{
		auto chain = std::make_shared<JunuoAsyncCallChain<void>>();
		chain->m_future = std::async(std::launch::async, [task, chain] { task(); });
		return chain;
	}

	template<typename NextT>
	std::shared_ptr<JunuoAsyncCallChain<NextT>> then(std::function<NextT()> nextTask)
	{
		auto next = std::make_shared<JunuoAsyncCallChain<NextT>>();
		next->m_future = std::async(std::launch::async, [nextTask, next, this] { m_future.get(); return nextTask(); });
		return next;
	}

private:
	std::future<void> m_future;

	template<typename T>
	friend class JunuoAsyncCallChain;
};
