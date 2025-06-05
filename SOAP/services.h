#pragma once

//gsoap ns service name: CalcService
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://example.com/calc.wsdl
//gsoap ns service location: http://localhost:8080

int ns__add(double a, double b, double* result);
int ns__subtract(int a, int b, int* result);