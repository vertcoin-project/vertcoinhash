#include <node.h>
#include <node_buffer.h>
#include <nan.h>

#include "Lyra2RE.h"
#include "scryptn.h"
#include "h2.h"

using v8::Exception;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Context;
using v8::Isolate;

void SumLyra2REv2(const v8::FunctionCallbackInfo<Value>& args) {
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> target = args[0]->ToObject(context).ToLocalChecked();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  lyra2re2_hash(input, output);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void SumLyra2REv3(const v8::FunctionCallbackInfo<Value>& args) {
 
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> target = args[0]->ToObject(context).ToLocalChecked();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  lyra2re3_hash(input, output);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void SumLyra2RE(const v8::FunctionCallbackInfo<Value>& args) {
 
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> target = args[0]->ToObject(context).ToLocalChecked();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  lyra2re_hash(input, output);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void SumScryptN(const v8::FunctionCallbackInfo<Value>& args) {
 
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> target = args[0]->ToObject(context).ToLocalChecked();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  scrypt_N_R_1_256(input, output, 2048, 1, 80);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void SumVerthash(const v8::FunctionCallbackInfo<Value>& args) {
 
  // Init will return if already initialized
  if(init_verthash() != 0) {
    Nan::ThrowTypeError("Verthash initialization failed");
    return;
  }

  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> target = args[0]->ToObject(context).ToLocalChecked();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  const unsigned char* input = (unsigned char*)node::Buffer::Data(target);
  unsigned char* output = new unsigned char[32];

  verthash_hash(input, 80, output);
  
  args.GetReturnValue().Set(Nan::NewBuffer(reinterpret_cast<char*>(output), 32).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "SumLyra2REv3", SumLyra2REv3);
  NODE_SET_METHOD(exports, "SumLyra2REv2", SumLyra2REv2);
  NODE_SET_METHOD(exports, "SumLyra2RE", SumLyra2RE);
  NODE_SET_METHOD(exports, "SumScryptN", SumScryptN);
  NODE_SET_METHOD(exports, "SumVerthash", SumVerthash);
}

NODE_MODULE(vertcoinhash, Init) 
