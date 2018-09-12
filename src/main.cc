#include "serilizer_basic_test.hh"
#include "test_fbs_wrapper.hh" 

int main(int argc, char*argv[])
{
    int vt[2000] = {0};
    std::cout << "Starting FlatBuffer test"<< std::endl << vt;

    test_root_msg fbs_test;
    std::cout << "Data before serialize"<<std::endl;
    fbs_test.initialize_default();
    fbs_test.print_message_contents();
    uint8_t *ret = NULL;
    int len = 0;
    std::tie(ret, len) = fbs_test.serialize_message();

    //for (int i = 0; i < len; i++) {
    //    printf (" %d", int(ret[i]));
    //}
    if (!ret || len < 0) {
        std::cout << "FlatBuffer test Failed"<< std::endl;
        exit(EXIT_FAILURE);
    }
    
    test_root_msg fbs_test1;
    std::cout << "\n\n\nData after Deserialize"<<std::endl;
    fbs_test1.deserialize_message((uint8_t*)ret, len);
    fbs_test1.print_message_contents();

    std::cout << "FlatBuffer test completed successfully "<< std::endl;
}
