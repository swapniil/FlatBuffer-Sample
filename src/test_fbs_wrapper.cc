#include "serilizer_basic_test.hh" 
#include "test_fbs_wrapper.hh" 


test_root_msg::test_root_msg() {
}

void test_root_msg::initialize_default() {
    short_field = 100;
    long_field = 10000L;
    int_field = 1000; 
    byte_field = 'A';
    name = "test-message";

    struct_long_field = 20000L;
    nest_long_field = 30000L;

    nested_struct_short_field = 500;
    nested_struct_long_field = 50000L;


    struct_short_field = 200;

    for (int8_t i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

}
test_root_msg::~test_root_msg() {
}

std::tuple<uint8_t*, int> test_root_msg::serialize_message() {
    flatbuffers::FlatBufferBuilder fbuff(1024);
    auto teststruct =  test_struct(struct_short_field, struct_long_field);

    auto nested_teststruct =  test_struct(nested_struct_short_field, nested_struct_long_field);

    auto sdta_brr = Createnested_test_table(fbuff, nest_long_field, &nested_teststruct);

    std::vector<int8_t> int_vector;

    for (int8_t i = 0; i < 5; i++) {
        int_vector.push_back(arr[i]);
    }

    auto intvctr = fbuff.CreateVector(int_vector);
    auto namestr = fbuff.CreateString(name);
    auto flat_data = CreateTest_msg(
                                    fbuff, 
                                    long_field, 
                                    int_field, 
                                    short_field,
                                    byte_field,
                                    intvctr,
                                    namestr,        
                                    &teststruct,
                                    sdta_brr
                                 ); 
    fbuff.Finish(flat_data);
    return std::tuple<uint8_t*,int>(fbuff.GetBufferPointer(), fbuff.GetSize());
}

bool test_root_msg::deserialize_message(uint8_t* buff, int len) {
    bool ret = false;
    if (!buff) {
        return ret;
    }
    flatbuffers::Verifier verifier(buff, len);
    if (false == VerifyTest_msgBuffer(verifier)) {
        std::cout << "Passed buffer is incorrect to deserialize as Test_msg" << std::endl;
        return false;
    }

    auto rootmsg = GetTest_msg(buff);
    if (!rootmsg) {
        std::cout << "Incorrect values in buffer to parse!!" << std::endl;
        return ret;
    }
    
    long_field = rootmsg->long_field();
    short_field = rootmsg->short_field();
    int_field = rootmsg->int_field();
    byte_field = rootmsg->byte_field();
    name = rootmsg->name()->str();

    auto uintarr = rootmsg->arr_field();
    for (int8_t i = 0; i < 5; i++) {
        arr[i] = uintarr->Get(i); 
    }

    auto nest_tbl = static_cast<const nested_test_table*> (rootmsg->table_field());
    auto nest_tbl_struct = static_cast<const test_struct*> (nest_tbl->nest_table_struct_field());
    auto naked_struct_field = static_cast<const test_struct*> (rootmsg->struct_field());


    nest_long_field = nest_tbl->log_field();
    nested_struct_short_field = nest_tbl_struct->short_field();
    nested_struct_long_field = nest_tbl_struct->long_field();

    struct_short_field = naked_struct_field->short_field(); 
    struct_long_field = naked_struct_field->long_field();
    return ret;
}

void test_root_msg::print_message_contents() {
    std::cout << "Root long field " << long_field  << std::endl;
    std::cout << "Root short field " << short_field<< std::endl;
    std::cout << "Root int field " << int_field << std::endl;
    std::cout << "Root byte field " << byte_field << std::endl;
    std::cout << "Root string field " << name << std::endl;
    std::cout << "Root byte array field ";
    for (uint8_t i = 0; i < 5; i++) {
        std::cout << " " << int(arr[i]);
    }
    std::cout<<std::endl;

    std::cout << "Struct long field " << struct_long_field << std::endl;
    std::cout << "Struct short field " << struct_short_field << std::endl;

    std::cout << "Nested table long field " << nest_long_field << std::endl;
    std::cout << "Nested table Struct long field " << nested_struct_long_field << std::endl;
    std::cout << "Nested table Struct short field " << nested_struct_short_field << std::endl;
}

