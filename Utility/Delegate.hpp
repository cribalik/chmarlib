/**
 * Main template for delgates
 *
 * \tparam return_type  return type of the function that gets captured
 * \tparam params       variadic template list for possible arguments
 *                      of the captured function
 *
 *
 * \example 
 * 
 *
 * struct A { void fun(int,int); };
 * void g_fun(int,int);
 *
 * A a;
 * Delegate<void(int,int)> d = DELEGATE(&A::fun, &a);
 * d(1,3); // Calls a.fun(1,3) !
 *
 * Delegate<void(int,int)> dg = DELEGATE2(&g_fun);
 * dg(1,3); // Calls g_fun(1,3) !
 *
 * Delegate<int(string)> d_def;
 * d_def("hello"); // Does nothing; default delegate is empty function
 */
 
template<typename return_type, typename... params>
class Delegate;

template<typename return_type, typename... params>
class Delegate<return_type(params...)>
{
    typedef return_type (*Pointer2Function)(void* callee, params...);
public:
    Delegate(void* callee, Pointer2Function function)
        : fpCallee(callee)
        , fpCallbackFunction(function)
    {}

    Delegate() 
        : fpCallee(nullptr)
        , fpCallbackFunction(&nullfun)
    {}
    
    return_type operator()(params... xs) const
    {
        return (*fpCallbackFunction)(fpCallee, xs...);
    }

    bool operator==(const Delegate& other) const
    {
        return (fpCallee == other.fpCallee)
               && (fpCallbackFunction == other.fpCallbackFunction);
    }


private:

    void* fpCallee;
    Pointer2Function fpCallbackFunction;
    
    static return_type nullfun(void*, params...) {}
};

/**
 * A DelegateFactory is used to create a Delegate for a certain method call.
 * It takes care of setting up the function that will cast the object that is stored
 * inside the Delegate back to the correct type.
 */
template<typename T, typename return_type, typename... params>
struct DelegateFactory
{
    template<return_type (T::*Func)(params...)>
    static return_type MethodCaller(void* o, params... xs)
    {
        return (static_cast<T*>(o)->*Func)(xs...);
    }

    template <return_type (*TFnctPtr)(params...)>
    static return_type FunctionCaller(void*, params... xs)
    {
        return (TFnctPtr)(xs...);
    }

    template<return_type (T::*Func)(params...)>
    inline static Delegate<return_type(params...)> Create(T* o)
    {
        return Delegate<return_type(params...)>(o, &DelegateFactory::MethodCaller<Func>);
    }

    template<return_type (*TFnctPtr)(params...)>
    inline static Delegate<return_type(params...)> CreateForFunction()
    {
        return Delegate<return_type(params...)>(nullptr, &DelegateFactory::FunctionCaller<TFnctPtr>);
    }
};
/**
 * helper function that is used to deduce the template arguments.
 * will return a DelegateFactory
 */
template<typename T, typename return_type, typename... params>
DelegateFactory<T, return_type, params... > MakeDelegate(return_type (T::*)(params...))
{
    return DelegateFactory<T, return_type, params...>();
}
class no_type{};
template<typename return_type, typename... params>
DelegateFactory<no_type, return_type, params... > MakeDelegate2(return_type (*TFnctPtr)(params...))
{
    return DelegateFactory<no_type, return_type, params...>();
}

#define DELEGATE(func, thisPrt) (MakeDelegate(func).Create<func>(thisPrt))
#define DELEGATE2(func) (MakeDelegate2(func).CreateForFunction<func>())

