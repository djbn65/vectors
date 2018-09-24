/* Define all your MyVector-related functions here.
 * You do not need to include the h file.
 * It included this file at the bottom.
 */

template <typename T>
void swap(T &a, T &b)
{
  T tmp = a;
  a = b;
  b = tmp;

  return;
}

 template <typename T>
 T & MyVector<T>::operator[](int i)
 {
   return m_data[i];
 }

template <typename T>
MyVector<T>::MyVector()
{
  m_data = nullptr;
  reserved_size = 0;
  data_size = 0;
}

template <typename T>
int MyVector<T>::capacity()
{
  return reserved_size;
}

template <typename T>
int MyVector<T>::size()
{
  return data_size;
}

template <typename T>
void MyVector<T>::clear()
{
  if (m_data != nullptr)
    delete[] m_data;
  data_size = 0;
  reserved_size = 0;
  m_data = nullptr;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &source)
{
  reserved_size = source.reserved_size;
  data_size = source.data_size;
  if (source.m_data != nullptr)
  {
    m_data = new T[source.reserved_size];
    for (int i = 0; i < source.data_size; i++)
      m_data[i] = source.m_data[i];
  }
  else
    m_data = nullptr;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> &source)
{
  clear();
  reserved_size = source.reserved_size;
  data_size = source.data_size;
  if (source.m_data != nullptr)
  {
    m_data = new T[source.reserved_size];
    for (int i = 0; i < source.data_size; i++)
      m_data[i] = source.m_data[i];
  }

  return *this;
}

// We're giving you this one for free
// and as a guide for the syntax.
template <typename T>
MyVector<T>::~MyVector()
{
  clear();
}

// Another example: remember, return type first,
// then scope just before the function name.
template <typename T>
T & MyVector<T>::at(int index)
{
  try
  {
    if (index >= data_size)
      throw OutOfBoundsException();
    return m_data[index];
  }
  catch (OutOfBoundsException &e)
  {
    cout << "Error occurred: " << e.what() << endl;
  }
}

template <typename T>
T& MyVector<T>::front()
{
  return m_data[0];
}

template <typename T>
T& MyVector<T>::back()
{
  return m_data[data_size-1];
}

template <typename T>
void MyVector<T>::reserve(int new_cap)
{
  if (new_cap > reserved_size)
  {
    MyVector<T> temp(*this);
    clear();
    m_data = new T[new_cap];
    reserved_size = new_cap;
    data_size = temp.data_size;
    for (int i = 0; i < temp.data_size; i++)
      m_data[i] = temp.m_data[i];
  }

  return;
}

template <typename T>
void MyVector<T>::shrink_to_fit()
{
  if (data_size != 0)
  {
    MyVector<T> temp(*this);
    clear();
    m_data = new T[2*temp.data_size];
    reserved_size = 2*temp.data_size;
    data_size = temp.data_size;
    for (int i = 0; i < temp.data_size; i++)
      m_data[i] = temp.m_data[i];
  }
  else
  {
    clear();
  }

  return;
}

template <typename T>
void MyVector<T>::assign(int count, const T &value)
{
  clear();
  if (count > reserved_size)
  {
    reserve(count);
  }

  for (int i = 0; i < count; i++)
    m_data[i] = value;

  data_size = count;

  if ((1.0/4) * reserved_size >= data_size)
    shrink_to_fit();

  return;
}

template <typename T>
void MyVector<T>::push_back(const T &x)
{
  if (m_data == nullptr)
    reserve(2);
  else if (data_size == reserved_size)
    reserve(2*data_size);

  m_data[data_size] = x;

  data_size++;

  if (data_size == reserved_size)
    reserve(2*data_size);

  return;
}

template <typename T>
void MyVector<T>::pop_back()
{
  if (data_size > 0)
    data_size--;

  if ((1.0/4) * reserved_size >= data_size)
    shrink_to_fit();

  return;
}

template <typename T>
void MyVector<T>::insert(int i, const T &x)
{
  try
  {
    if (i > data_size || i < 0)
      throw OutOfBoundsException();
  }
  catch (OutOfBoundsException &e)
  {
    cout << "Error Occurred: " << e.what() << endl;
    return;
  }
  if (data_size == reserved_size)
    reserve(data_size*2);

  for (int j = end()-1; j >= i; j--)
    m_data[j+1] = m_data[j];

  m_data[i] = x;
  data_size++;

  if (data_size == reserved_size)
    reserve(2*data_size);

  return;
}

template <typename T>
void MyVector<T>::remove(int i)
{
  try
  {
    if (i > data_size || i < 0)
      throw OutOfBoundsException();
  }
  catch (OutOfBoundsException &e)
  {
    cout << "Error Occurred: " << e.what() << endl;
    return;
  }

  for (int j = i+1; j < data_size; j++)
    m_data[j-1] = m_data[j];

  data_size--;

  if ((1.0/4)*reserved_size >= data_size)
    shrink_to_fit();

  return;
}
