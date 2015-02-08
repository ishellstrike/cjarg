#ifndef CASTER_H
#define CASTER_H
#include <memory>

class Caster
{
private:
        static int next_typeid()
        {
            static int magic(0);
            return magic++;
        }

        struct CasterValueBase
        {
            int id;

            CasterValueBase(const int m) :
                id(m)
            {
            }

            virtual ~CasterValueBase()
            {
            }
        };

        template <typename T_>
        struct CasterValue :
            CasterValueBase
        {
            T_ value;

            CasterValue(const T_ & v) :
                CasterValueBase(typeid_for<T_>()),
                value(v)
            {
            }
        };



    public:
        std::shared_ptr<CasterValueBase> _value;
        template <typename T_>
        static int typeid_for()
        {
            static int result(next_typeid());
            return result;
        }

        template <typename T_>
        Caster(const T_ &t) :
            _value(new CasterValue<T_>(t))
        {
        }

        template <typename T_>
        T_ &as() const
        {
            auto reqid = typeid_for<T_>();
            if (reqid != _value->id)
                throw;
            return std::static_pointer_cast<CasterValue<T_>>(_value)->value;
        }

        template <typename T_>
        bool is() const
        {
            auto reqid = typeid_for<T_>();
            if (reqid != _value->id)
                return false;
            return true;
        }
};

#endif // CASTER_H
