/*
  WiFi.h - Library for Arduino Wifi shield.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "WiFi.h"
#include "mbed.h"
#include "utility/http_request.h"
#include "utility/https_request.h"

static FILE* target;

void body_callback(const char* data, uint32_t data_len) {
	fwrite(data, 1, data_len, target);
}

int WiFiClass::download(char* url, const char* target_file) {
	target = fopen(target_file, "wb");
  HttpsRequest* req = new HttpsRequest(getNetwork(), nullptr, HTTP_GET, url, &body_callback);
	if (req->send(NULL, 0) == NULL)
  {
    fclose(target);
    return req->get_error();
  }
  int const size = ftell(target);
  fclose(target);
  return size;
}
