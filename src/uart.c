#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include <mraa.h>
#include <errno.h>

#define IV_GET(name) mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, (name)))
#define IV_SET(name, value)                                                    \
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, (name)), value)
#define UART_DEFAULT_BUFSIZE  1024
#define UART_DEFAULT_TIMEOUT  1000
#define UART_DEFAULT_BAUDRATE 9600
#define UART_DEFAULT_PROMPT   ">"

static void uart_close(mrb_state *mrb, void *p) {
  if (p != NULL) {
    free(p);
  }
}

static struct mrb_data_type mrb_mraa_uart_ctx_type = {"MraaUartContext",
                                                      uart_close};

mrb_value mrb_mraa_uart_init(mrb_state *mrb, mrb_value self) {
  mrb_int dev, baud, nargs;
  mraa_uart_context uart;

  nargs = mrb_get_args(mrb, "i|i", &dev, &baud);
  if (nargs < 2)
    baud = UART_DEFAULT_BAUDRATE;

  uart = mraa_uart_init(dev);

  if (uart == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize DEV:%S.",
               mrb_fixnum_value(dev));
  }
  
  mrb_data_init(self, uart, &mrb_mraa_uart_ctx_type);
  // DATA_TYPE(self) = &mrb_mraa_uart_ctx_type;
  // DATA_PTR(self) = uart;
  IV_SET("@read_bufsize", mrb_fixnum_value(UART_DEFAULT_BUFSIZE));
  IV_SET("@timeout", mrb_fixnum_value(UART_DEFAULT_TIMEOUT));
  IV_SET("@prompt", mrb_str_new_cstr(mrb, UART_DEFAULT_PROMPT));
  mrb_funcall(mrb, self, "baudrate=", 1, mrb_fixnum_value(baud));
  return self;
}

mrb_value mrb_mraa_uart_set_baudrate(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  mraa_result_t result;
  mrb_int baud;
  mrb_get_args(mrb, "i", &baud);

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);

  result = mraa_uart_set_baudrate(uart, baud);
  if (result != MRAA_SUCCESS) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Could not set baudrate");
  }
  IV_SET("@baudrate", mrb_fixnum_value(baud));
  return self;
}

mrb_value mrb_mraa_uart_set_timeout(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  mraa_result_t result;
  mrb_int r, w, ic; // read, write, interchar
  mrb_get_args(mrb, "iii", &r, &w, &ic);

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);
  result = mraa_uart_set_timeout(uart, r, w, ic);
  switch (result) {
  case MRAA_SUCCESS:
    break;
  case MRAA_ERROR_FEATURE_NOT_IMPLEMENTED:
    mrb_raise(mrb, E_RUNTIME_ERROR, "Feature not implemneted by MRAA");
    break;
  }
  IV_SET("@read_to", mrb_fixnum_value(r));
  IV_SET("@write_to", mrb_fixnum_value(w));
  IV_SET("@interchar_to", mrb_fixnum_value(ic));
  return self;
}

mrb_value mrb_mraa_uart_get_dev_path(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;

  const char *path;

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);

  path = mraa_uart_get_dev_path(uart);

  return mrb_str_new_cstr(mrb, path);
}

mrb_value mrb_mraa_uart_write(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  mraa_result_t result;
  char *string;
  size_t l = 0;
  mrb_get_args(mrb, "s", &string, &l);

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);
  result = mraa_uart_write(uart, string, l);
  if (result < 0) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Could not write (err %S)",
               mrb_fixnum_value(result));
  }
  return mrb_fixnum_value(result);
}

mrb_value mrb_mraa_uart_read(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  mraa_result_t result;
  char *string;
  mrb_value mrb_result;
  int bufsize;

  if ((bufsize = mrb_fixnum(IV_GET("@read_bufsize"))) <= 0)
    bufsize = UART_DEFAULT_BUFSIZE;

  string = calloc(bufsize, sizeof(char));

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);
  result = mraa_uart_read(uart, string, bufsize);
  if (result < 0) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Could not read (err %S)",
               mrb_fixnum_value(result));
  }
  mrb_result = mrb_str_new_cstr(mrb, string);
  free(string);
  return mrb_result;
}

mrb_value mrb_mraa_uart_data_available(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  unsigned int millis, nargs;
  nargs = mrb_get_args(mrb, "|i", &millis);
  if (nargs == 0)
    millis = 0;

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);
  return ( mraa_uart_data_available(uart, millis) == 1 ) ? mrb_true_value() : mrb_false_value();
}

mrb_value mrb_mraa_uart_stop(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  mraa_result_t result;

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);

  result = mraa_uart_stop(uart);
  if (result != MRAA_SUCCESS) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Could not stop port");
  }
  return self;
}

mrb_value mrb_mraa_uart_flush(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  mraa_result_t result;

  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);

  result = mraa_uart_flush(uart);
  if (result != MRAA_SUCCESS) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Could not flush port");
  }
  return self;
}


mrb_value mrb_mraa_uart_read_to_prompt(mrb_state *mrb, mrb_value self) {
  mraa_uart_context uart;
  mrb_int timeout, nargs, i;
  char prompt, str_arg[1], buf[1];
  mrb_value result;  
  
  timeout = mrb_fixnum(IV_GET("@timeout"));
  
  nargs = mrb_get_args(mrb, "|z", &str_arg);
  if (nargs == 0) {
    char *str = mrb_str_to_cstr(mrb, IV_GET("@prompt"));
    prompt = str[0];
  }
  else
    prompt = str_arg[0];
  
  uart = (mraa_uart_context)mrb_data_get_ptr(mrb, self, &mrb_mraa_uart_ctx_type);
  result = mrb_str_buf_new(mrb, mrb_fixnum(IV_GET("@read_bufsize")));
  
  while (mraa_uart_data_available(uart, timeout) > 0) {
    i = mraa_uart_read(uart, buf, 1);
    if (i == 0)         break;
    if (*buf == prompt) break;
    result = mrb_str_cat_cstr(mrb, result, buf);
  }

  return result;
}
