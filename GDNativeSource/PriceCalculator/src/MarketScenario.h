#ifndef MARKETSCENARIO_H
#define MARKETSCENARIO_H

#include <map>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace pca {
    class CMarket;
    class CProduct;
    class COption;
    class CReality;

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

        struct RealityData {
            std::vector<std::string> vProducts;
            std::map<std::string, std::string> mapOptionToProduct;
            std::map<std::string, std::vector<std::string>> mapComplCombos;
            std::map<std::string, std::map<std::string, double>> mapSupplCombos;
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
        RealityData m_realityData;
        std::map<std::string, double> m_mapPrices;
        std::map<std::string, double> m_mapMarketWarehouse;
        std::vector<PersonData> m_vPersonsData;

    private:
        void CaptureReality(CReality* pReality);
        void ApplyReality(CReality* pReality);
    };

    // Helper functions for JSON serialization (needed by nlohmann::json)
    void to_json(nlohmann::json& j, const CMarketScenario::PersonData& p);
    void from_json(const nlohmann::json& j, CMarketScenario::PersonData& p);
    void to_json(nlohmann::json& j, const CMarketScenario::RealityData& r);
    void from_json(const nlohmann::json& j, CMarketScenario::RealityData& r);
}

#endif // MARKETSCENARIO_H
