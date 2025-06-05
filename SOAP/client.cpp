//
// Created by oleh.slabak on 6/5/2025.
//

#include "soapCalcServiceProxy.h"
#include "CalcService.nsmap"
#include <iostream>

int main() {
    CalcServiceProxy proxy;
    proxy.soap_endpoint = "http://localhost:8080";

    int result = 0;
    if (proxy.ns__add(5, 3, &result) == SOAP_OK) {
        std::cout << "5 + 3 = " << result << std::endl;
    } else {
        proxy.soap_stream_fault(std::cerr);
    }

    if (proxy.ns__subtract(10, 4, &result) == SOAP_OK) {
        std::cout << "10 - 4 = " << result << std::endl;
    } else {
        proxy.soap_stream_fault(std::cerr);
    }

    return 0;
}