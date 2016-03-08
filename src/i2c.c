#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mraa.h>

static void
i2c_close(mrb_state *mrb, void *p){
    if (p != NULL){
        mraa_i2c_stop((mraa_i2c_context)p);
    }
}

static struct mrb_data_type mrb_mraa_i2c_ctx_type = {
    "MraaI2cContext", i2c_close
};

mrb_value
mrb_mraa_i2c_init(mrb_state *mrb, mrb_value self){
    mrb_int bus;
    mrb_bool raw;
    mraa_i2c_context i2c;

    raw = false;
    mrb_get_args(mrb, "i|b", &bus, &raw);

    if (raw == false){
        i2c = mraa_i2c_init(bus);
    }
    else {
        i2c = mraa_i2c_init_raw(bus);
    }

    if (i2c == NULL){
        mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize BUS:%S.", mrb_fixnum_value(bus));
    }

    DATA_TYPE(self) = &mrb_mraa_i2c_ctx_type;
    DATA_PTR(self) = i2c;

    return self;
}

mrb_value
mrb_mraa_i2c_frequency(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int freq;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &freq);
    result = mraa_i2c_frequency(i2c, freq);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_i2c_read(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int length;

    uint8_t *rbuf;
    mrb_int num_of_read;
    int ai, i;

    mrb_value mrv_rbuf;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &length);

    rbuf = (uint8_t*)mrb_malloc(mrb, sizeof(uint8_t) * length);
    memset(rbuf, 0, sizeof(uint8_t) * length);

    num_of_read = mraa_i2c_read(i2c, rbuf, length);

    mrv_rbuf = mrb_ary_new_capa(mrb, num_of_read);
    ai = mrb_gc_arena_save(mrb);
    for (i = 0; i < num_of_read; i++){
        mrb_ary_push(mrb, mrv_rbuf, mrb_fixnum_value(rbuf[i]));
        mrb_gc_arena_restore(mrb, ai);
    }

    mrb_free(mrb, rbuf);

    return mrb_assoc_new(mrb, mrv_rbuf, mrb_fixnum_value(num_of_read));
}

mrb_value
mrb_mraa_i2c_read_byte(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;

    uint8_t rdata;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    rdata = mraa_i2c_read_byte(i2c);

    return mrb_fixnum_value(rdata);
}

mrb_value
mrb_mraa_i2c_read_reg(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int reg;

    uint8_t rdata;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &reg);
    rdata = mraa_i2c_read_byte_data(i2c, reg);

    return mrb_fixnum_value(rdata);
}

mrb_value
mrb_mraa_i2c_read_word_reg(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int reg;

    uint16_t rdata;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &reg);
    rdata = mraa_i2c_read_word_data(i2c, reg);

    return mrb_fixnum_value(rdata);
}

mrb_value
mrb_mraa_i2c_write(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_value mrv_wbuf;
    mrb_int length;

    mraa_result_t result;
    uint8_t *wbuf;
    mrb_int argc;
    
    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    argc = mrb_get_args(mrb, "o|i", &mrv_wbuf, &length);

    result = MRAA_ERROR_INVALID_PARAMETER;
    if (mrb_array_p(mrv_wbuf)){
        int i;
        if (argc == 1){
            length = RARRAY_LEN(mrv_wbuf);
        }

        wbuf = (uint8_t *)mrb_malloc(mrb, sizeof(uint8_t) * length);
        memset(wbuf, 0, sizeof(uint8_t) * length);
        for (i = 0; i < length; i++){
            wbuf[i] = mrb_fixnum(mrb_ary_ref(mrb, mrv_wbuf, i));
        }
        result = mraa_i2c_write(i2c, wbuf, length);
        mrb_free(mrb, wbuf);
    }

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_i2c_write_byte(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int wdata;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &wdata);
    result = mraa_i2c_write_byte(i2c, wdata & 0xFF);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_i2c_write_reg(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int wdata;
    mrb_int reg;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "ii", &wdata, &reg);
    result = mraa_i2c_write_byte_data(i2c, wdata & 0xFF, reg);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_i2c_write_word_reg(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int wdata;
    mrb_int reg;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "ii", &wdata, &reg);
    result = mraa_i2c_write_word_data(i2c, wdata & 0xFFFF, reg);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_i2c_address(mrb_state *mrb, mrb_value self){
    mraa_i2c_context i2c;
    mrb_int addr;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_i2c_ctx_type, i2c);

    mrb_get_args(mrb, "i", &addr);
    result = mraa_i2c_address(i2c, addr);

    return mrb_fixnum_value(result);
}

