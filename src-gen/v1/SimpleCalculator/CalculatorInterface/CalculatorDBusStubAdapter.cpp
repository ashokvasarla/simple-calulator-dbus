/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.12.v201706201043.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <v1/SimpleCalculator/CalculatorInterface/Calculator.hpp>
#include <v1/SimpleCalculator/CalculatorInterface/CalculatorDBusStubAdapter.hpp>

namespace v1 {
namespace SimpleCalculator {
namespace CalculatorInterface {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createCalculatorDBusStubAdapter(
                   const CommonAPI::DBus::DBusAddress &_address,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< CalculatorDBusStubAdapter<::v1::SimpleCalculator::CalculatorInterface::CalculatorStub>>(_address, _connection, std::dynamic_pointer_cast<::v1::SimpleCalculator::CalculatorInterface::CalculatorStub>(_stub));
}

void initializeCalculatorDBusStubAdapter() {
    CommonAPI::DBus::Factory::get()->registerStubAdapterCreateMethod(
        Calculator::getInterface(), &createCalculatorDBusStubAdapter);
}

INITIALIZER(registerCalculatorDBusStubAdapter) {
    CommonAPI::DBus::Factory::get()->registerInterface(initializeCalculatorDBusStubAdapter);
}

} // namespace CalculatorInterface
} // namespace SimpleCalculator
} // namespace v1
