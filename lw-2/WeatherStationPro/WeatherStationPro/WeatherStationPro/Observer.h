#pragma once


template <typename T>
class IObservable;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T>& observable) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, unsigned priority = 0) override
	{
		m_observersMap.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		const auto tmp = m_observersMap;
		for (auto &item : tmp)
		{
			item.second->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		for (auto it = m_observersMap.cbegin(); it != m_observersMap.cend(); ++it)
		{
			if (it->second == &observer)
			{
				m_observersMap.erase(it);
				break;
			}
		}

	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::multimap<unsigned, ObserverType *> m_observersMap;
};

