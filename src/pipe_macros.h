#define SELECT_PIPE(x) pipe* __active_pipe = &x
#define MAKE_PROC __active_pipe->map_managed_processor
#define GET_PROC __active_pipe->get_processor
#define PROC __active_pipe->process_with
#define PROC_IP __active_pipe->process_with_inplace

#define SINE_FILL(HZ, TARGET) sine::fill_buffer( HZ, __active_pipe->get_mapped_buffer(TARGET))

#define BUF_MAP __active_pipe->assign_ptr_buffer
#define BUF_ALLOC __active_pipe->create_buffer
#define BUF_CP __active_pipe->copy_into
#define BUF_MAX(x,y) y = __active_pipe->find_max(x)
#define BUF_GAIN_DB(x,db) __active_pipe->multiply_into_scalar(x, volume::db2vol(db), x )
#define BUF_SQUARE(x) __active_pipe->multiply_into( x, x, x );
#define BUF_SQUARE_INTO(x,y) __active_pipe->multiply_into( x, y );
#define BUF_MUL(x,y) __active_pipe->multiply_into(x,y,x);
#define BUF_MUL_INTO(x,y,z) __active_pipe->multiply_into(x,y,z);
#define BUF_FMUL(x,y) __active_pipe->multiply_into_scalar(x, y, x)
#define BUF_ADD(x,y) __active_pipe->add_into(x,y,x)
#define BUF_ADD_INTO(x,y,z) __active_pipe->add_into(x,y,z)
#define BUF_DIFF(x,y) __active_pipe->difference_into(x,y,x)
#define BUF_DIFF_INTO(x,y,z) __active_pipe->difference_into(x,y,z)
#define BUF_XFADE_INTO(a,b,o,c) __active_pipe->xfade_into_using(a,b,o,c)
#define BUF_UPMIX(x) __active_pipe->upmix(x)
#define BUF_DITHER(x,db) __active_pipe->dither_buffer(x,db)

#define INVERT(x) x = 1.0 / x
#define DB2VOL(x) volume::db2vol(x)
#define FMUL(x,y) x = x*y;
