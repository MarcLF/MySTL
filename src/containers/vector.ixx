export module mystl:vector;

import std;

export namespace mystl {
template<typename T>
class vector
{
  public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;

    // Constructor
    vector()
      : data_(nullptr)
      , size_(0)
      , capacity_(0)
    {
    }

    // Copy Constructor
    vector(const vector& other)
      : data_(nullptr)
      , size_(0)
      , capacity_(0)
    {
        reserve(other.size_);
        for (size_type i = 0; i < other.size_; ++i) {
            new (data_ + i) T(other.data_[i]);
        }
        size_ = other.size_;
    }

    // Move Constructor: marked noexcept so std algos can optimize its use.
    vector(vector&& other) noexcept
      : data_(other.data_)
      , size_(other.size_)
      , capacity_(other.capacity_)
    {
        // Reset the other vector so its destructor doesn't free
        // the memory we just took.
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~vector()
    {
        clear();

        ::operator delete(data_);
    }

    /**
     * Accesses the element at the given index.
     * No bounds checking is performed.
     */
    reference operator[](size_type index) { return data_[index]; }

    /**
     *  Const version of the index operator.
     *  Required for read-access when the vector itself is const.
     */
    const T& operator[](size_type index) const { return data_[index]; }

    vector& operator=(const vector& other)
    {
        if (this != &other) {
            clear();
            reserve(other.size_);
            for (size_type i = 0; i < other.size_; ++i) {
                new (data_ + i) T(other.data_[i]);
            }
            size_ = other.size_;
        }
        return *this;
    }

    vector& operator=(vector&& other) noexcept
    {
        if (this != &other) // Prevent self-assignment
        {
            clear();
            ::operator delete(data_);

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Basic Accessors
    size_type size() const noexcept { return size_; }
    size_type capacity() const noexcept { return capacity_; }
    bool empty() const noexcept { return size_ == 0; }

    /**
     * Ensures there is enough room for at least new_capacity elements.
     * This handles the heavy lifting of reallocating memory.
     */
    void reserve(size_type new_capacity)
    {
        // Only grow, never shrink with reserve
        if (new_capacity <= capacity_) {
            return;
        }

        // Grab a new block of raw memory.
        // ::operator new allocates bytes but does not call constructors.
        T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));

        // Move existing objects from the old block to the new block.
        for (size_type i = 0; i < size_; ++i) {
            // Placement New: new (pointer_address) T(constructor_arguments);
            new (new_data + i) T(std::move_if_noexcept(data_[i]));

            data_[i].~T();
        }

        // Release the old raw memory block.
        ::operator delete(data_);

        // Update pointers and bookkeeping
        data_ = new_data;
        capacity_ = new_capacity;
    }

    // Adds an element to the end of the vector.
    void push_back(const T& value)
    {
        if (size_ == capacity_) {
            // Growth strategy: if empty, 1; otherwise, double the current size.
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        // Construct the new element in the first available slot of raw memory.
        new (data_ + size_) T(value);
        ++size_;
    }

    void push_back(T&& value)
    {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (data_ + size_) T(std::move(value)); // Move into the vector
        ++size_;
    }

    /*
     * Constructs an element directly in the vector's memory (more efficient).
     * Uses variadic templates (...) to pass any number of arguments to T's
     * constructor.
     */
    template<typename... Args>
    reference emplace_back(Args&&... args)
    {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        // 'std::forward' ensures the arguments keep their lvalue/rvalue
        // properties as they are passed into the constructor.
        T* p = new (data_ + size_) T(std::forward<Args>(args)...);
        ++size_;
        return *p;
    }

    /*
     *  Destroys all elements but keeps the allocated memory (capacity remains).
     */
    void clear() noexcept
    {
        // We must call destructors because T might own resources (like
        // strings/pointers).
        for (size_type i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }

  private:
    // Pointer to the first element in the raw buffer
    T* data_;

    size_type size_;
    size_type capacity_;
};
} // namespace mystl