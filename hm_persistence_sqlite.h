/*
The MIT License

Copyright (c) 2014- High-Mobility GmbH (https://high-mobility.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef HM_PERSISTENCE_SQLITE_H
#define HM_PERSISTENCE_SQLITE_H

#include <stdint.h>

// SQUNUSED macro
#define SQUNUSED(x) (void)(sizeof(x))

void hm_persistence_sqlite_add_access_cert(uint8_t *serial, uint8_t *cert, uint8_t size);
void hm_persistence_sqlite_get_access_cert(uint8_t *serial, uint8_t *cert, uint8_t *size);
void hm_persistence_sqlite_remove_access_cert(uint8_t *serial);

#endif //HM_PERSISTENCE_SQLITE_H
