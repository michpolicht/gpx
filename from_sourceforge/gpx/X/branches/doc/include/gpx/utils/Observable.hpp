/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_OBSERVABLE_HPP_
#define GPX_X_UTILS_OBSERVABLE_HPP_

#include <list>

//#note: "IObserver.hpp" included below

namespace gpx {
namespace utils {

template <class> class IObserver;

/**
 * Observable. Observable object is able to notify registered objects, known as observers,
 * about certain events or state changes.
 */
template <class C>
class Observable
{
	public:
		/**
		 * Observable event.
		 */
		class Event
		{
			public:
				Event(C * o, int type = 0);

				C * observable() const;

				int type() const;

			private:
				C * m_observable;
				int m_type;
		};

	public:
		/**
		 * Add observer. To be notified by observable, object must be added to the
		 * list of observers.
		 * @param o object to be added to the observers list.
		 */
		void addObserver(IObserver<C> * o);

		/**
		 * Remove observer. Removes object from the list of observers.
		 * @param o object to be removed from the observers list.
		 */
		void removeObserver(IObserver<C> * o);

	protected:
		typedef std::list<IObserver<C> *> ObserversContainer;

	protected:
		/**
		 * Notify observers. Observable should call this method, whenever it wants
		 * to notify observers about certain event or state change.
		 * @param type event type.
		 */
		void notifyObservers(int type = 0);

	protected:
		/**
		 * Get observers list.
		 * @return list of observers.
		 */
		ObserversContainer & observers();

		/**
		 * Get observers list (const version).
		 * @return list of observers.
		 */
		const ObserversContainer & observers() const;

	private:
		ObserversContainer m_observers;
};

}
}


//this include belongs to implementation
#include "IObserver.hpp"

namespace gpx {
namespace utils {

template <class C>
inline
Observable<C>::Event::Event(C * o, int type):
		m_observable(o),
		m_type(type)
{
}

template <class C>
inline
C * Observable<C>::Event::observable() const
{
	return m_observable;
}

template <class C>
inline
int Observable<C>::Event::type() const
{
	return m_type;
}



template <class C>
inline
void Observable<C>::addObserver(IObserver<C> * o)
{
	m_observers.push_back(o);
}

template <class C>
inline
void Observable<C>::removeObserver(IObserver<C> * o)
{
	m_observers.remove(o);
}



template <class C>
inline
void Observable<C>::notifyObservers(int type)
{
	for (typename ObserversContainer::iterator i = m_observers.begin(); i != m_observers.end(); ++i)
		(*i)->event(typename Observable<C>::Event(static_cast<C *>(this), type));
}

template <class C>
inline
typename Observable<C>::ObserversContainer & Observable<C>::observers()
{
	return m_observers;
}

template <class C>
inline
const typename Observable<C>::ObserversContainer & Observable<C>::observers() const
{
	return m_observers;
}


}
}


#endif /* GPX_X_UTILS_OBSERVABLE_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
