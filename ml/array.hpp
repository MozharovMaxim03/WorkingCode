#include "utils.hpp"

namespace ml {
	template<typename ValueType>
	class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
	{
	public:
		ListIterator(ValueType* p) : p(p) {}
		ListIterator(const ListIterator& it) : p(it.p) {}

		bool operator!=(const ListIterator& other) const
		{
			return p != other.p;
		}
		bool operator==(const ListIterator& other) const
		{
			return p == other.p;
		}
		typename ListIterator::reference operator*() const
		{
			return *p;
		}
		ListIterator& operator++()
		{
			++p;
			return *this;
		}
	private:
		ValueType* p;
	};

	template <typename T, size_t len>
	struct list {
		T arr[len];

		list(T* darr) {
			for (size_t i = 0; i < len; i++)
				arr[i] = darr[i];
		};
		list() {}

		typedef ListIterator<T> iterator;
		typedef ListIterator<const T> const_iterator;

		size_t size() const {
			return len;
		}

		T operator[](const size_t i) const {
			return arr[i];
		}
		T& operator[](const size_t i) {
			return arr[i];
		}

		T* data() {
			return arr;
		}
		T* data_copy() const {
			T* a = new T[len];
			for (size_t i = 0; i < len; i++)
				a[i] = arr[i];
			return a;
		}

		operator vec<T>() const {
			vec<T> a = vec<T>(len);
			for (size_t i = 0; i < len; i++)
				a[i] = arr[i];
			return a;
		}

		iterator begin() {
			return iterator(arr);
		}
		const_iterator begin() const {
			return const_iterator(arr);
		}
		iterator end() {
			return iterator(arr + size());
		}
		const_iterator end() const {
			return const_iterator(arr + size());
		}
	};

	template <typename T>
	struct arrlist {
		T* arr;
		const size_t len;

		arrlist(const size_t dlen) : arr{ new T[dlen] }, len{ dlen } {}
		arrlist(const size_t dlen, T* darr) : arrlist(dlen) {
			for (size_t i = 0; i < len; i++)
				arr[i] = darr[i];
		}
		arrlist(vec<T> v) : arrlist(v.size(), v.data()) {}
		arrlist(const arrlist& v) : arrlist(v.size(), v.arr) {}
		~arrlist() {
			delete arr;
		}

		typedef ListIterator<T> iterator;
		typedef ListIterator<const T> const_iterator;

		size_t size() const {
			return len;
		}

		T operator[](const size_t i) const {
			return arr[i];
		}
		T& operator[](const size_t i) {
			return arr[i];
		}

		T* data() {
			return arr;
		}
		T* data_copy() const {
			T* a = new T[len];
			for (size_t i = 0; i < len; i++)
				a[i] = arr[i];
			return a;
		}

		operator vec<T>() const {
			vec<T> a = vec<T>(len);
			for (size_t i = 0; i < len; i++)
				a[i] = arr[i];
			return a;
		}

		iterator begin() {
			return iterator(arr);
		}
		const_iterator begin() const {
			return const_iterator(arr);
		}
		iterator end() {
			return iterator(arr + size());
		}
		const_iterator end() const {
			return const_iterator(arr + size());
		}
	};

	template <typename T>
	struct arraylist {
		std::vector<T> value;

		arraylist() {};
		arraylist(vec<T> darr) : value{ darr } {};
		template <size_t s> arraylist(list<T, s> darr) : value{ darr } {};
		arraylist(const T* darr, const size_t dsize) : arraylist(vec<T>(dsize)) {
			for (size_t i = 0; i < size(); i++)
				value[i] = darr[i];
		};

		typedef ListIterator<T> iterator;
		typedef ListIterator<const T> const_iterator;

		size_t size() const {
			return value.size();
		}

		T operator[](const size_t i) const {
			return value[i];
		}
		T& operator[](const size_t i) {
			return value[i];
		}

		inline void add_end(const T item) {
			value.push_back(item);
		}
		template <size_t s> void adds_end(const list<T, s> items) {
			for (size_t i = 0; i < items.size(); i++)
				value_end(items[i]);
		}
		void adds_end(const arrlist<T> items) {
			for (size_t i = 0; i < items.size(); i++)
				add_end(items[i]);
		}
		void adds_end(const arraylist items) {
			for (size_t i = 0; i < items.size(); i++)
				add_end(items[i]);
		}
		void adds_end(const vec<T> items) {
			for (size_t i = 0; i < items.size(); i++)
				add_end(items[i]);
		}

		void add_start(const T item) {
			value.push_back(item);
			for (size_t i = 1; i < size(); i++)
				value[size() - i] = value[size() - 1 - i];
			value[0] = item;
		}
		template <size_t s> void adds_start(const list<T, s> items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size(); i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[i] = items[i];
		}
		void adds_start(const arraylist items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size(); i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[i] = items[i];
		}
		void adds_start(const arrlist<T> items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size(); i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[i] = items[i];
		}
		void adds_start(const vec<T> items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size(); i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[i] = items[i];
		}

		void add(const size_t index, const T item) {
			value.push_back(item);
			for (size_t i = 0; i < size() - index; i++)
				value[size() - 1 - i] = value[size() - 2 - i];
			value[index] = item;
		}
		template <size_t s> void adds(const size_t index, const list<T, s> items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size() - index; i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[index + i] = items[i];
		}
		void adds(const size_t index, const arraylist items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size() - index; i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[index + i] = items[i];
		}
		void adds(const size_t index, const arrlist<T> items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size() - index; i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[index + i] = items[i];
		}
		void adds(const size_t index, const vec<T> items) {
			for (size_t i = 0; i < items.size(); i++)
				value.push_back(items[i]);
			for (size_t i = items.size(); i < size() - index; i++)
				value[size() - 1 + items.size() - i] = value[size() - 1 - i];
			for (size_t i = 0; i < items.size(); i++)
				value[index + i] = items[i];
		}

		T rmv_end() {
			T v = value[value.size() - 1];
			value.pop_back();
			return v;
		}
		arrlist<T> rmvs_end(const size_t count) {
			arrlist<T> v = count;
			for (size_t i = 0; i < count; i++)
			{
				v[count - 1 - i] = value[value.size() - 1];
				value.pop_back();
			}
			return v;
		}

		T rmv_start() {
			T v = value[0];
			for (size_t i = 0; i < size() - 1; i++)
				value[i] = value[i + 1];
			value.pop_back();
			return v;
		}
		arrlist<T> rmvs_start(const size_t count) {
			arrlist<T> v = count;
			for (size_t i = 0; i < count; i++)
				v[i] = value[i];
			for (size_t i = 0; i < size() - count; i++)
				value[i] = value[i + count];
			for (size_t i = 0; i < count; i++)
				value.pop_back();;
			return v;
		}

		T rmv(const size_t index) {
			T v = value[index];
			for (size_t i = index; i < size() - 1; i++)
				value[i] = value[1 + i];
			value.pop_back();
			return v;
		}
		arrlist<T> rmvs(const size_t index, const size_t count) {
			arrlist<T> v = count;
			for (size_t i = 0; i < count; i++)
				v[i] = value[index+i];
			for (size_t i = index + count; i < size(); i++)
				value[i - count] = value[i];
			for (size_t i = 0; i < count; i++)
				value.pop_back();;
			return v;
		}

		T* data() {
			return value.data();
		}
		T* data_copy() const {
			T* a = new T[size()];
			for (size_t i = 0; i < size(); i++)
				a[i] = value[i];
			return a;
		}

		inline operator vec<T>() const {
			return value;
		}
		inline operator arrlist<T>() const {
			return value;
		}

		auto begin() {
			return value.begin();
		}
		auto begin() const {
			return value.begin();
		}
		auto end() {
			return value.end();
		}
		auto end() const {
			return value.end();
		}
	};
}