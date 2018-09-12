#include "serilizer_basic_test.hh" 
#include "test_generated.h"

using namespace test;
class test_root_msg {
    public:
        long long_field, struct_long_field, nest_long_field;
        short struct_short_field, short_field;

        short nested_struct_short_field;
        long nested_struct_long_field;
        std::string name;
        int8_t arr[5], byte_field;
        uint32_t int_field;


        test_root_msg();
        ~test_root_msg();

        std::tuple<uint8_t*, int>  serialize_message();
        bool deserialize_message(uint8_t*, int);
        void print_message_contents();
        void initialize_default();
        inline bool verify_msg(uint8_t* buff, int len) {
            flatbuffers::Verifier verifier(buff, len);
            return VerifyTest_msgBuffer(verifier);
        }
};
