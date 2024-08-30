#include <gtest/gtest.h>
#include "MPointer.h"

class MPointerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Inicialización si es necesario
    }

    void TearDown() override {
        // Limpieza si es necesario
    }
};

TEST_F(MPointerTest, TestConstructor) {
    auto ptr = MPointer<int>::New();
    ASSERT_NE(ptr.GetID(), 0);  // Asegura que el ID no es cero
}

TEST_F(MPointerTest, TestCopyConstructor) {
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 100;
    MPointer<int> ptr2 = ptr1;
    ASSERT_EQ(*ptr1, *ptr2);
    ASSERT_EQ(ptr1.GetID(), ptr2.GetID());
}

TEST_F(MPointerTest, TestAssignmentOperator) {
    auto ptr1 = MPointer<int>::New();
    auto ptr2 = MPointer<int>::New();
    *ptr1 = 100;
    ptr2 = ptr1;
    ASSERT_EQ(*ptr2, 100);
}

TEST_F(MPointerTest, TestDereferenceOperators) {
    auto ptr = MPointer<int>::New();
    *ptr = 123;
    ASSERT_EQ(*ptr, 123);
    ASSERT_EQ(*&ptr, 123);
}

TEST(MPointerGCTest, TestRegisterDeregister) {
    auto ptr = new int(10);  // Simular un puntero a un entero
    int id = MPointerGC::GetInstance().RegisterPointer(ptr, [](void* p) { delete (int*)p; });
    ASSERT_NE(id, 0);
    MPointerGC::GetInstance().DeregisterPointer(id);
    // Aquí se podría verificar el estado interno o contar los elementos registrados si se expone esa información
}

TEST(MPointerGCTest, TestRefCount) {
    auto ptr = new int(10);
    int id = MPointerGC::GetInstance().RegisterPointer(ptr, [](void* p) { delete (int*)p; });
    MPointerGC::GetInstance().IncrementRefCount(id);
    MPointerGC::GetInstance().DecrementRefCount(id);
    // Verificar que el ref_count volvió a su valor inicial
}
