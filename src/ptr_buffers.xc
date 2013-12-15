#include "ptr_buffers.h"

[[distributable]]
void uint_ptr_buffer_rx_slave(server interface uint_ptr_tx tx,
                              server interface uint_ptr_rx_slave rx)
{
  unsigned * movable entry;
  int occupied = 0;
  while (1) {
    select {
    case !occupied => tx.push(unsigned * movable p):
      entry = move(p);
      occupied = 1;
      rx.ready();
      break;
    case occupied => rx.pop() -> unsigned * movable p:
      p = move(entry);
      occupied = 0;
      break;
    }
  }
}

[[distributable]]
void uint_ptr_buffer_tx_slave(server interface uint_ptr_tx_slave tx,
                              server interface uint_ptr_rx rx)
{
  unsigned * movable entry;
  int occupied = 0;
  tx.ready();
  while (1) {
    select {
    case !occupied => tx.push(unsigned * movable p):
      entry = move(p);
      occupied = 1;
      break;
    case occupied => rx.pop() -> unsigned * movable p:
      p = move(entry);
      occupied = 0;
      tx.ready();
      break;
    }
  }
}

[[distributable]]
void uint_ptr_buffer(server interface uint_ptr_tx tx,
                     server interface uint_ptr_rx rx)
{
  unsigned * movable entry;
  int occupied = 0;
  while (1) {
    select {
    case !occupied => tx.push(unsigned * movable p):
      entry = move(p);
      occupied = 1;
      break;
    case occupied => rx.pop() -> unsigned * movable p:
      p = move(entry);
      occupied = 0;
      break;
    }
  }
}
