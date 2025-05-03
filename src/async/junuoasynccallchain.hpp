#pragma once

#include <functional>
#include <future>
#include <memory>
#include <thread>

template<typename T>
class JunuoAsyncCallChain : public std::enable_shared_from_this<JunuoAsyncCallChain<T>>
{
public:
	using Task = std::function<T()>;
	static std::shared_ptr<JunuoAsyncCallChain<T>> run(Task task);
	template<typename NextT>
	std::shared_ptr<JunuoAsyncCallChain<NextT>> then(std::function<NextT(T)> nextTask);

private:
	std::future<T> m_future;
	T m_result{};
	bool m_ready = false;

	std::function<void(T)> m_nextTask;
	std::shared_ptr<void> m_next;

	void triggerNext(T value);
};

template<typename T>
std::shared_ptr<JunuoAsyncCallChain<T>> JunuoAsyncCallChain<T>::run(Task task)
{
	auto chain = std::make_shared<JunuoAsyncCallChain<T>>();
	chain->m_future = std::async(std::launch::async, [task, chain] {
		T result = task();
		chain->m_result = result;
		chain->m_ready = true;
		chain->triggerNext(result);
		return result;
		});
	return chain;
}

template<typename T>
template<typename NextT>
std::shared_ptr<JunuoAsyncCallChain<NextT>> JunuoAsyncCallChain<T>::then(std::function<NextT(T)> nextTask)
{
	auto next = std::make_shared<JunuoAsyncCallChain<NextT>>();
	m_nextTask = [nextTask, next](T val) {
		next->m_future = std::async(std::launch::async, [nextTask, next, val] {
			NextT result = nextTask(val);
			next->m_result = result;
			next->m_ready = true;
			next->triggerNext(result);
			return result;
			});
		};
	if (m_ready)
		m_nextTask(m_result);
	m_next = next;
	return next;
}

template<typename T>
void JunuoAsyncCallChain<T>::triggerNext(T value)
{
	if (m_nextTask)
		m_nextTask(value);
}
