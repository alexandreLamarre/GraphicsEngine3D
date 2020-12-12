#include "../vector.h"
#include <vector>

/**
 * Function that handles Vectorf unittests for its constructors
 * @return Tester object containing the results of the unittests
 */
Tester vector_constructor_tests(){
    std::string test_name = "vector ";
    Tester VT = Tester(test_name);
    // =================== Constructor ================================

    // =========== default ===========
    std::string fm = "Default declaration should be the zero vector";
    Vectorf<1> v1 = Vectorf<1>();
    float res1[2]{0.0,0.0};
    VT.add(v1.get() == res1, fm, res1, v1.get());

    Vectorf<2> v2 = Vectorf<2>();
    float res2[3]{0.0, 0.0};
    VT.add(v2.get() == res2, fm, res2, v2.get());

    Vectorf<3> v3 = Vectorf<3>();
    float res3[4]{0.0, 0.0, 0.0, 0.0};
    VT.add(v3.get() == res3, fm, res3, v3.get());

    Vectorf<4> v4 = Vectorf<4>();
    float res4[5]{0.0, 0.0, 0.0, 0.0, 0.0};
    VT.add(v4.get() == res4, fm, res4, v4.get());

    // ========== initializer list
    std::string fm1 = "Incorrect Constructor behaviour";

    Vectorf<1> v5{};
    float res5[2]{0.0,0.0};
    VT.add(v5.get() == res5, fm1, res5, v5.get());


    Vectorf<1> v6{1.3};
    float res6[2]{1.3,0.0};
    VT.add(v6.get() == res6, fm1, res6, v6.get());


    Vectorf<1> v7{2.2, 2.3};
    float res7[2]{2.2, 2.3};
    VT.add(v7.get() == res7, fm1, res7, v7.get());

    Vectorf<1> v8{66, 32, 653, 3 ,3 ,4 ,1, 5};
    float res8[2]{66,32};
    VT.add(v8.get() == res8, fm1, res8, v8.get());

    Vectorf<2> v9{};
    float res9[3]{};
    VT.add(v9.get() == res9, fm1, res9, v9.get());

    Vectorf<2> v10{1.3};
    float res10[3]{1.3, 0.0, 0.0};
    VT.add(v10.get() == res10, fm1, res10, v10.get());

    Vectorf<2> v11{2.2, 2.3};
    float res11[3]{2.2, 2.3, 0.0};
    VT.add(v11.get() == res11, fm1, res11, v11.get());

    Vectorf<2> v12{66, 32, 653, 3 ,3 ,4 ,1, 5};
    float res12[3]{66,32,653};
    VT.add(v12.get() == res12, fm1, res12, v12.get());

    Vectorf<3> v13{};
    float res13[4]{0.0, 0.0 ,0.0, 0.0};
    VT.add(v13.get() == res13, fm1, res13, v13.get());

    Vectorf<3> v14{1.3};
    float res14[4]{1.3, 0.0 ,0.0, 0.0};
    VT.add(v14.get() == res14, fm1, res14, v14.get());

    Vectorf<3> v15{2.2, 2.3};
    float res15[4]{2.2, 2.3 ,0.0, 0.0};
    VT.add(v15.get() == res15, fm1, res15, v15.get());

    Vectorf<3> v16{2.2,2.4,2.5};
    float res16[4]{2.2, 2.4, 2.5, 0.0};
    VT.add(v16.get() == res16, fm1, res16, v16.get());

    Vectorf<3> v17{66, 32, 653, 3 ,3 ,4 ,1, 5};
    float res17[4]{66,32,653,3};
    VT.add(v17.get() == res17, fm1, res17, v17.get());
    return VT;

}

Tester vector_std_operators(){
    std::string test_name = "addition/subtraction/dotproduct";
    std::string add_fail = "Vector addition error";
    std::string sub_fail = "Vector subtraction error";
    std::string dot_fail = "Vector dot product error";
    Tester VT= Tester(test_name);
    Vectorf<3> v1{1.0,1.0,1.0};
    Vectorf<3> v2{1.0,1.0,1.0};
    Vectorf<3> v3 = v1+v2;

    float res1[4]{2.0,2.0,2.0, 0.0};
    VT.add(v3.get() == res1, add_fail,  res1, v3.get());

    Vectorf<3> v4 = v1-v2;
    float res2[4]{0.0,0.0,0.0,0.0};
    VT.add(v4.get() == res2, sub_fail, res2, v4.get());

    float v5 = v1*v2;
    float res3 = 3.0;
    VT.add(v5 == res3, dot_fail, res3, v5);

    return VT;
}

Tester vector_prod_tests(){
    std::string test_name = "vector scalar/cross product";
    std::string scalar_fail = "scalar product error";
    Tester VT = Tester(test_name);

    //============= scalar product ========================
    float c1 = 1.0;
    float c2 = 5.5;
    float c3 = -1.2;

    Vectorf<3> v1 = Vectorf<3>{};
    Vectorf<3> v2 = Vectorf<3>{1.0, 1.0, 1.0};
    Vectorf<3> v3 = Vectorf<3> {-2.0, 1.5, -3.5};

    float res1[4]{0.0, 0.0, 0.0, 0.0};
    Vectorf<3> u1 = c1*v1;
    VT.add(u1.get() == res1, scalar_fail, res1, u1.get());

    Vectorf<3> u2 = c2*v1;
    VT.add(u2.get() == res1, scalar_fail, res1, u2.get());

    Vectorf<3> u3 = c3*v1;
    VT.add(u3.get(), scalar_fail, res1, u3.get());


    float res2[4]{1.0, 1.0, 1.0, 0.0};
    Vectorf<3> u4 = c1*v2;
    VT.add(u4.get() == res2, scalar_fail, res2, u4.get());

    float res3[4]{5.5, 5.5, 5.5, 0.0};
    Vectorf<3> u5 = c2*v2;
    VT.add(u5.get() == res3, scalar_fail, res3, u5.get());

    float res4[4]{-1.2, -1.2, -1.2, 0.0};
    Vectorf<3> u6 = c3*v2;
    VT.add(u6.get() == res4, scalar_fail, res4, u6.get());

    float res5[4]{-2.0, 1.5, -3.5};
    Vectorf<3> u7 = c1*v3;
    VT.add(u7.get() == res5, scalar_fail, res5, u7.get());

    float res6[4]{-11.0, 8.25, -19.25};
    Vectorf<3> u8 = c2*v3;
    VT.add(u8.get() == res6, scalar_fail, res6, u8.get());

    float res7[4]{2.4, -1.8, 4.2};
    Vectorf<3> u9 = c3*v3;
    VT.add(u9.get() == res7, scalar_fail, res7, u9.get());

    // ============ cross product =====================



    return VT;
}

std::vector<Tester> vectorTests(){
    std::vector<Tester> tests;
    tests.push_back(vector_constructor_tests());
    tests.push_back(vector_std_operators());
    tests.push_back(vector_prod_tests());


    return tests;
}

