//
// Created by oleh.slabak on 6/5/2025.
//
#include "soapCalcServiceService.h"
#include "soapCalcServiceService.nsmap"


int ns__add(struct soap *soap, int a, int b, int *result) {
    *result = a + b;
    return SOAP_OK;
}

int ns__subtract(struct soap *soap, int a, int b, int *result) {
    *result = a - b;
    return SOAP_OK;
}

int main() {
    CalcServiceService service(SOAP_XML_INDENT);
    if (service.run(8080)) {
        service.soap_stream_fault(std::cerr);
    }
    return 0;
}
