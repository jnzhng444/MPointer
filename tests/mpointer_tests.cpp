#include <gtest/gtest.h>
#include "MPointer.h"
#include "MPointerGC.h"

class MPointerTestSuite : public ::testing::Test {
protected:
    void SetUp() override {
        // Limpiar el recolector de basura antes de cada prueba
        MPointerGC::GetInstance().CollectGarbage();
    }
};

// Prueba de creación básica y asignación de valores
TEST_F(MPointerTestSuite, BasicAllocation) {
    auto ptr = MPointer<int>::New();
    *ptr = 42;
    ASSERT_EQ(*ptr, 42);  // Verifica que el valor asignado sea correcto
}

// Prueba de constructor de copia
TEST_F(MPointerTestSuite, CopyConstructor) {
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 42;

    auto ptr2 = ptr1;
    ASSERT_EQ(*ptr2, 42);  // Verifica que el valor en ptr2 sea correcto
    ASSERT_EQ(ptr1.GetID(), ptr2.GetID());  // Ambos deben compartir el mismo ID
}

// Prueba de asignación a `nullptr`
TEST_F(MPointerTestSuite, NullptrAssignment) {
    auto ptr = MPointer<int>::New();
    *ptr = 100;
    ASSERT_EQ(*ptr, 100);

    ptr = nullptr;
    ASSERT_EQ(ptr.GetID(), -1);  // Verifica que el puntero esté invalidado
}

// Prueba de sobrecarga de operador *
TEST_F(MPointerTestSuite, DereferenceOperator) {
    auto ptr = MPointer<int>::New();
    *ptr = 100;
    ASSERT_EQ(*ptr, 100);  // Verifica que la dereferencia funcione correctamente
}

// Prueba de sobrecarga de operador &
TEST_F(MPointerTestSuite, AddressOperator) {
    auto ptr = MPointer<int>::New();
    int* addr = &*ptr;
    ASSERT_NE(addr, nullptr);  // Asegura que la dirección del puntero no sea nula
}

// Prueba de múltiples referencias
TEST_F(MPointerTestSuite, MultipleReferences) {
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 42;

    auto ptr2 = ptr1;
    auto ptr3 = ptr1;

    ASSERT_EQ(*ptr1, 42);
    ASSERT_EQ(*ptr2, 42);
    ASSERT_EQ(*ptr3, 42);

    *ptr3 = 100;
    ASSERT_EQ(*ptr1, 100);
    ASSERT_EQ(*ptr2, 100);
    ASSERT_EQ(*ptr3, 100);
}

// Prueba del recolector de basura
TEST_F(MPointerTestSuite, GarbageCollector) {
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 42;

    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 1);

    auto ptr2 = ptr1;
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 2);

    ptr2 = nullptr;
    MPointerGC::GetInstance().CollectGarbage();
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 1);

    ptr1 = nullptr;
    MPointerGC::GetInstance().CollectGarbage();
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(1), -1);  // ID ya no debe existir
}

// Prueba del ciclo de vida del puntero
TEST_F(MPointerTestSuite, DestructorAndGarbageCollection) {
    {
        auto ptr1 = MPointer<int>::New();
        *ptr1 = 42;
        ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 1);
    }
    MPointerGC::GetInstance().CollectGarbage();
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(1), -1);  // ID ya no debe existir
}


// Prueba del recolector de basura basada en ref_count
TEST(MPointerGCTest, GarbageCollectorRefCount) {
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 42;

    // Verificar que el puntero esté registrado y tenga ref_count = 1
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 1);

    // Crear una nueva referencia
    auto ptr2 = ptr1;
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 2);

    // Eliminar una referencia y verificar que el contador de referencias disminuya
    ptr2 = nullptr;
    MPointerGC::GetInstance().CollectGarbage();  // Recolectar basura de manera explícita
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 1);

    // Eliminar la referencia original y verificar que el puntero se recoja
    ptr1 = nullptr;
    MPointerGC::GetInstance().CollectGarbage();  // Recolectar basura nuevamente
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(1), -1);  // Verificar que el ID ya no exista
}




// Prueba de la asignación de punteros entre sí
TEST_F(MPointerTestSuite, AssignmentOperator) {
    auto ptr1 = MPointer<int>::New();
    *ptr1 = 42;
    auto ptr2 = MPointer<int>::New();
    *ptr2 = 100;

    ptr2 = ptr1;
    ASSERT_EQ(*ptr2, 42);
    ASSERT_EQ(ptr1.GetID(), ptr2.GetID());
}

// Prueba del método GetID()
TEST_F(MPointerTestSuite, GetIDTest) {
    auto ptr = MPointer<int>::New();
    ASSERT_GT(ptr.GetID(), 0);
}

// Prueba específica para el Garbage Collector
TEST(MPointerGCTest, GarbageCollectorWorks) {
    // Crear varios punteros dentro de un bloque para que se destruyan automáticamente
    {
        auto ptr1 = MPointer<int>::New();
        *ptr1 = 100;

        auto ptr2 = MPointer<int>::New();
        *ptr2 = 200;

        auto ptr3 = MPointer<int>::New();
        *ptr3 = 300;

        // Verificar que el garbage collector tenga todos los punteros registrados
        ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr1.GetID()), 1);
        ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr2.GetID()), 1);
        ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(ptr3.GetID()), 1);
    }

    // Forzar la recolección de basura
    MPointerGC::GetInstance().CollectGarbage();

    // Verificar que los punteros hayan sido eliminados por el recolector de basura
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(1), -1);  // ptr1 debería haber sido recolectado
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(2), -1);  // ptr2 debería haber sido recolectado
    ASSERT_EQ(MPointerGC::GetInstance().GetRefCount(3), -1);  // ptr3 debería haber sido recolectado
}