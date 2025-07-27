template <typename T>
class ControlBlock {
public:
    T* ptr;
    int strongCount;
    int weakCount;

    ControlBlock(T* p) : ptr(p), strongCount(1), weakCount(0) {}
    ~ControlBlock() = default;
};

template<typename T>
class WeakPtr {
private:
    ControlBlock<T>* control;

public:
    WeakPtr() : control(nullptr) {}

    WeakPtr(const SharedPtr<T>& shared) {
        control = shared.control;
        if (control) control->weakCount++;
    }

    WeakPtr(const WeakPtr& other) {
        control = other.control;
        if (control) control->weakCount++;
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            control = other.control;
            if (control) control->weakCount++;
        }
        return *this;
    }

    void release() {
        if (control) {
            control->weakCount--;
            if (control->weakCount == 0 && control->strongCount == 0)
                delete control;
            control = nullptr;
        }
    }

    ~WeakPtr() {
        release();
    }

    bool expired() const {
        return !control || control->strongCount == 0;
    }

    SharedPtr<T> lock() const {
        if (!expired())
            return SharedPtr<T>(*this); // create SharedPtr from WeakPtr
        return SharedPtr<T>(nullptr);
    }
};

