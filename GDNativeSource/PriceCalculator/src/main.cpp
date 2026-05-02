#include <iostream>
#include <chrono>
#include "Reality.h"
#include "Market.h"
#include "Person.h"
#include "Utils.h"

using namespace std;
using namespace pca;

int main()
{
    cout << "--- PriceCalculator: Market Simulation ---" << endl;

    // 1. Inicializar el entorno (Realidad y Mercado)
    CReality oReality;
    CMarket oMarket(&oReality);

    // 2. Crear población de agentes
    pca::CPerson* pP1 = oMarket.CreatePerson("Person 1");
    pca::CPerson* pP2 = oMarket.CreatePerson("Person 2");
    pca::CPerson* pP3 = oMarket.CreatePerson("Person 3");

    // 3. Dotación inicial de productos
    for (auto* pProd : oReality.GetProducts()) {
        pP1->AddProductAmount(pProd, 1.0);
        pP2->AddProductAmount(pProd, 1.0);
        pP3->AddProductAmount(pProd, 1.0);
    }

    cout << "Configuración inicial lista. Generando gráficas de partida..." << endl;
    CUtils::PrintInitialConditionsToFile(&oMarket);
    CUtils::PrintSatisfactionCurvesToFile(&oMarket);
    CUtils::ShowGraphics("--initial");

    // 4. Ejecutar Simulación de Ajuste de Precios
    cout << "Calculando equilibrio de mercado..." << endl;
    auto start = chrono::high_resolution_clock::now();

    oMarket.CalculateNewPrices();
    oMarket.ExecuteTrades();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    
    // 5. Mostrar resultados y gráficas finales
    cout << "Simulación completada en " << elapsed.count() << " segundos." << endl;
    CUtils::PrintPrices(oMarket.GetPricesRef());
    
    CUtils::PrintPersonsOptionAdjustmentToFile(&oMarket);
    CUtils::ShowGraphics();

    cout << "\nProceso finalizado con éxito." << endl;
    return 0;
}
