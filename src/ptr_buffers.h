#ifndef PTR_BUFFERS_H_
#define PTR_BUFFERS_H_

#ifdef __XC__
interface uint_ptr_tx {
  [[guarded]] void push(unsigned * movable p);
};

interface uint_ptr_rx_slave {
  [[notification]] slave void ready();
  [[guarded, clears_notification]] unsigned * movable pop();
};

interface uint_ptr_tx_slave {
  [[notification]] slave void ready();
  [[guarded, clears_notification]] void push(unsigned * movable p);
};

interface uint_ptr_rx {
  [[guarded]] unsigned * movable pop();
};

[[distributable]]
void uint_ptr_buffer_rx_slave(server interface uint_ptr_tx tx,
                              server interface uint_ptr_rx_slave rx);

[[distributable]]
void uint_ptr_buffer_tx_slave(server interface uint_ptr_tx_slave tx,
                              server interface uint_ptr_rx rx);

[[distributable]]
void uint_ptr_buffer(server interface uint_ptr_tx tx,
                     server interface uint_ptr_rx rx);

#endif // __XC__

#endif // PTR_BUFFERS_H_
