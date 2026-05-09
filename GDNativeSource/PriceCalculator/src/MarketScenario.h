#ifndef MARKETSCENARIO_H
#define MARKETSCENARIO_H

#include <map>
#include <string>
#include <vector>

namespace pca {
    class CMarket;
    class CProduct;
    class COption;

    /**
     * @brief Clase para capturar, almacenar y aplicar un escenario completo de mercado.
     * Permite guardar el estado de precios, inventarios y curvas de satisfacción.
     */
    class CMarketScenario {
    public:
        struct PersonData {
            std::string sName;
            std::map<std::string, double> mapOwnedProducts;
            // Parámetros de satisfacción: <PreferenceAt0, MaximumSatisf>
            std::map<std::string, std::pair<double, double>> mapOptionSatisfaction;
            std::map<std::string, std::pair<double, double>> mapSupplSatisfaction;
            std::map<std::string, std::pair<double, double>> mapComplSatisfaction;
        };

        CMarketScenario();
        virtual ~CMarketScenario();

        /**
         * @brief Captura el estado actual de un mercado y lo guarda en este objeto.
         */
        void Capture(CMarket* pMarket);

        /**
         * @brief Aplica el estado guardado en este objeto a un mercado existente.
         * El mercado debe tener la misma estructura de productos/opciones (CReality).
         */
        void Apply(CMarket* pMarket);

        /**
         * @brief Guarda el escenario en un archivo JSON.
         */
        bool SaveToFile(const std::string& sFilePath);

        /**
         * @brief Carga un escenario desde un archivo JSON.
         */
        bool LoadFromFile(const std::string& sFilePath);

        // Datos del escenario
        std::map<std::string, double> m_mapPrices;
        std::map<std::string, double> m_mapMarketWarehouse;
        std::vector<PersonData> m_vPersonsData;

    private:
        // Métodos auxiliares para no repetir código
    };
}

#endif // MARKETSCENARIO_H
