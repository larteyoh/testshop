#include "fawazahmed0_currency.hpp"

#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <map>
#include <QString>

namespace {

const QString BASE_URL{
    QStringLiteral("https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies/%1/%2.json")};
} // namespace

std::optional<double> Fawazahmed0CurrencyApi::price(neroshop::Currency from, neroshop::Currency to) const
{
    // Fill map with initial currency ids
    std::map<neroshop::Currency, QString> CURRENCY_TO_ID;
    for (const auto& [key, value] : neroshop::CurrencyMap) {
        CURRENCY_TO_ID[std::get<0>(value)] = QString::fromStdString(key).toLower();
    }
    // Fill map with initial currency vs and codes
    std::map<neroshop::Currency, QString> CURRENCY_TO_VS;
    for (const auto& [key, value] : neroshop::CurrencyMap) {
        CURRENCY_TO_VS[std::get<0>(value)] = QString::fromStdString(key).toLower();
    }    

    auto it = CURRENCY_TO_ID.find(from);
    if (it == CURRENCY_TO_ID.cend()) {
        return std::nullopt;
    }
    const auto idFrom = it->second;

    it = CURRENCY_TO_VS.find(to);
    if (it == CURRENCY_TO_VS.cend()) {
        return std::nullopt;
    }
    const auto idTo = it->second;

    QNetworkAccessManager manager;
    QEventLoop loop;
    QObject::connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    const QUrl url(BASE_URL.arg(idFrom, idTo));
    auto reply = manager.get(QNetworkRequest(url));
    loop.exec();
    QJsonParseError error;
    const auto json_doc = QJsonDocument::fromJson(reply->readAll(), &error);
    if (error.error != QJsonParseError::NoError) {
        return std::nullopt;
    }
    const auto root_obj = json_doc.object();
    return root_obj.value(idTo).toDouble(); // for date: root_obj.value("date").toString()
}
