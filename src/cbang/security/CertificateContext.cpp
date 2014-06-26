/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

              Copyright (c) 2003-2014, Cauldron Development LLC
                 Copyright (c) 2003-2014, Stanford University
                             All rights reserved.

        The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
        as published by the Free Software Foundation, either version 2.1 of
        the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
        Lesser General Public License for more details.

        You should have received a copy of the GNU Lesser General Public
        License along with the C! library.  If not, see
        <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
        You may request written permission by emailing the authors.

                For information regarding this software email:
                               Joseph Coffland
                        joseph@cauldrondevelopment.com

\******************************************************************************/

#include "CertificateContext.h"

#include "Certificate.h"
#include "CSR.h"
#include "CRL.h"

#include <openssl/x509v3.h>

#include <stdlib.h>

using namespace cb;


CertificateContext::CertificateContext(const Certificate *issuer,
                                       const Certificate *subject,
                                       const CSR *request, const CRL *crl,
                                       int flags) {
  ctx = (X509V3_CTX *)malloc(sizeof(X509V3_CTX));
  X509V3_set_ctx(ctx, issuer ? issuer->getX509() : 0,
                 subject ? subject->getX509() : 0,
                 request ? request->getX509_REQ() : 0,
                 crl ? crl->getX509_CRL() : 0, flags);
}


CertificateContext::~CertificateContext() {
  free(ctx);
}
