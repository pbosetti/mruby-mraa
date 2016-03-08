#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mraa.h>

static void
spi_close(mrb_state *mrb, void *p){
    if (p != NULL){
        mraa_spi_stop((mraa_spi_context)p);
    }
}

static struct mrb_data_type mrb_mraa_spi_ctx_type = {
    "MraaSpiContext", spi_close
};

mrb_value
mrb_mraa_spi_init(mrb_state *mrb, mrb_value self){
    mrb_int bus;
    mrb_int cs;
    mraa_spi_context spi;

    mrb_int argc;

    argc = mrb_get_args(mrb, "i|i", &bus, &cs);

    if (argc == 1){
        spi = mraa_spi_init(bus);
    }
    else {
        spi = mraa_spi_init_raw(bus, cs);
    }

    if (spi == NULL){
        mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize BUS:%S.", mrb_fixnum_value(bus));
    }

    DATA_TYPE(self) = &mrb_mraa_spi_ctx_type;
    DATA_PTR(self) = spi;

    return self;
}

mrb_value
mrb_mraa_spi_mode(mrb_state *mrb, mrb_value self){
    mraa_spi_context spi;
    mrb_int mode;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_spi_ctx_type, spi);

    mrb_get_args(mrb, "i", &mode);
    result = mraa_spi_mode(spi, mode);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_spi_frequency(mrb_state *mrb, mrb_value self){
    mraa_spi_context spi;
    mrb_int freq;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_spi_ctx_type, spi);

    mrb_get_args(mrb, "i", &freq);
    result = mraa_spi_frequency(spi, freq);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_spi_transfer(mrb_state *mrb, mrb_value self){
    mraa_spi_context spi;
    mrb_value mrv_txbuf;
    mrb_int length;

    mraa_result_t result;
    uint8_t *rxbuf;
    uint8_t *txbuf;
    mrb_int argc;
    int ai;

    mrb_int num_of_tran;
    mrb_value mrv_rxbuf;

    num_of_tran = 0;
    mrv_rxbuf = mrb_nil_value();

    Data_Get_Struct(mrb, self, &mrb_mraa_spi_ctx_type, spi);

    argc = mrb_get_args(mrb, "o|i", &mrv_txbuf, &length);
    result = MRAA_ERROR_INVALID_PARAMETER;
    if (mrb_array_p(mrv_txbuf)){
        int i;
        if (argc == 1){
            length = RARRAY_LEN(mrv_txbuf);
        }

        // Rx buffer
        rxbuf = (uint8_t *)mrb_malloc(mrb, sizeof(uint8_t) * length);
        memset(rxbuf, 0, sizeof(uint8_t) * length);
        // Tx buffer
        txbuf = (uint8_t *)mrb_malloc(mrb, sizeof(uint8_t) * length);
        memset(txbuf, 0, sizeof(uint8_t) * length);
        for (i = 0; i < length; i++){
            txbuf[i] = mrb_fixnum(mrb_ary_ref(mrb, mrv_txbuf, i));
        }
        result = mraa_spi_transfer_buf(spi, txbuf, rxbuf, length);
        mrb_free(mrb, txbuf);

        if (result == MRAA_SUCCESS){
            num_of_tran = length;
            mrv_rxbuf = mrb_ary_new_capa(mrb, num_of_tran);
            ai = mrb_gc_arena_save(mrb);
            for (i = 0; i < num_of_tran; i++){
                mrb_ary_push(mrb, mrv_rxbuf, mrb_fixnum_value(rxbuf[i]));
                mrb_gc_arena_restore(mrb, ai);
            }
        }
        mrb_free(mrb, rxbuf);
    }

    return mrb_assoc_new(mrb, mrv_rxbuf, mrb_fixnum_value(num_of_tran));
}

mrb_value
mrb_mraa_spi_transfer_byte(mrb_state *mrb, mrb_value self){
    mraa_spi_context spi;
    mrb_int txbyte;

    uint8_t rxbyte;

    Data_Get_Struct(mrb, self, &mrb_mraa_spi_ctx_type, spi);

    mrb_get_args(mrb, "i", &txbyte);
    rxbyte = mraa_spi_write(spi, txbyte & 0xFF);

    return mrb_fixnum_value(rxbyte);
}

mrb_value
mrb_mraa_spi_lsbmode(mrb_state *mrb, mrb_value self){
    mraa_spi_context spi;
    mrb_bool lsbmode;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_spi_ctx_type, spi);

    mrb_get_args(mrb, "b", &lsbmode);
    result = mraa_spi_lsbmode(spi, lsbmode);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_spi_bit_per_word(mrb_state *mrb, mrb_value self){
    mraa_spi_context spi;
    mrb_int bit_per_word;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_spi_ctx_type, spi);

    mrb_get_args(mrb, "i", &bit_per_word);
    result = mraa_spi_bit_per_word(spi, bit_per_word);

    return mrb_fixnum_value(result);
}

