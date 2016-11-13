/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

              Copyright (c) 2003-2015, Cauldron Development LLC
                 Copyright (c) 2003-2015, Stanford University
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

#include "Object.h"
#include "Array.h"
#include "Context.h"
#include "SmartPop.h"

#include <cbang/log/Logger.h>

#include <duktape.h>

using namespace std;
using namespace cb::duk;


bool Object::has(const string &key) const {
  ctx.push(key);
  return duk_has_prop(ctx.getContext(), index) == 1;
}


bool Object::get(const string &key) const {
  ctx.push(key);
  return duk_get_prop(ctx.getContext(), index);
}


void Object::put(const string &key) {
  ctx.push(key);
  duk_insert(ctx.getContext(), -2);
  duk_put_prop(ctx.getContext(), index);
}


Array Object::toArray(const string &key) {
  get(key);
  return Array(ctx, ctx.top() - 1);
}


Object Object::toObject(const string &key) {
  get(key);
  return Object(ctx, ctx.top() - 1);
}


bool Object::toBoolean(const string &key) {
  get(key);
  SmartPop pop(ctx);
  return ctx.toBoolean();
}


int Object::toInteger(const string &key) {
  get(key);
  SmartPop pop(ctx);
  return ctx.toInteger();
}


double Object::toNumber(const string &key) {
  get(key);
  SmartPop pop(ctx);
  return ctx.toNumber();
}


void *Object::toPointer(const string &key) {
  get(key);
  SmartPop pop(ctx);
  return ctx.toPointer();
}


string Object::toString(const string &key) {
  get(key);
  SmartPop pop(ctx);
  return ctx.toString();
}


void Object::setNull(const string &key) {
  ctx.pushNull();
  put(key);
}


void Object::setBoolean(const string &key, bool x) {
  ctx.pushBoolean(x);
  put(key);
}


void Object::setPointer(const string &key, void *x) {
  ctx.pushPointer(x);
  put(key);
}


void Object::set(const string &key, int x) {
  ctx.push(x);
  put(key);
}


void Object::set(const string &key, unsigned x) {
  ctx.push(x);
  put(key);
}


void Object::set(const string &key, double x) {
  ctx.push(x);
  put(key);
}


void Object::set(const string &key, const string &x) {
  ctx.push(x);
  put(key);
}


void Object::set(const string &key, Object &obj) {
  ctx.dup(obj.getIndex());
  put(key);
}


void Object::set(const string &key, Array &ary) {
  ctx.dup(ary.getIndex());
  put(key);
}