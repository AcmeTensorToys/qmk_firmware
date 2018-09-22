#!/usr/bin/env python3

import argparse
import hidraw
import logging
import sys
import time

class HiddevWrapper() :
  def __init__(self, vend=0xFEED, prod=0xA502, sn=None, iface=1) :
    self.vend  = vend
    self.prod  = prod
    self.sn    = sn
    self.iface = iface

  def __enter__(self) :
    dev = hidraw.device()
    for d in hidraw.enumerate():
      logging.debug("Looking at v=%s pr=%s sn=%s if=%s p=%s",
            d['vendor_id'], d['product_id'], d['serial_number'],
            d['interface_number'], d['path'])
      if                         d['vendor_id']        != self.vend  : continue
      if                         d['product_id']       != self.prod  : continue
      if                         d['interface_number'] != self.iface : continue
      if self.sn is not None and d['serial_number']    != self.sn    : continue
      dev.open_path(d['path'])

      logging.debug("Checking version")
      r = dev.write([0, ord('V')] + [0] * 7)
      if r != 9 :
        logging.debug("Device handshake failed to send: %d", r)
        continue
      r = dev.read(8)
      if r[0:3] != [ord('V'), 0x00, 0xFF] :
        logging.debug("Device handshake mismatch: %r", r)
        dev.close()
        continue
      logging.debug("Device handshake OK: %r", r)
      self.dev = dev
      return dev
    else :
      raise ValueError("Device not found")

  def __exit__(self, type, value, traceback):
    self.dev.close()

def auto_int(x) : return int(x, 0)

def devwr(dev, buf) : return dev.write([0] + buf)

def do_leds_onoff(dw, cmd, _):
  if cmd == "ledon" : cmd = 0xF1
  else              : cmd = 0xF0
  with dw as dev :
    devwr(dev, [ord('U'), cmd])
    print(dev.read(8))

def do_all_hsv(dw, _, cliargs) :
  argp = argparse.ArgumentParser()
  argp.add_argument('hue', type=auto_int)
  argp.add_argument('sat', type=auto_int)
  argp.add_argument('val', type=auto_int)
  args = argp.parse_args(cliargs)

  args.hue &= 0xFF
  args.sat &= 0xFF
  args.val &= 0xFF

  with dw as dev :
    devwr(dev, [ord('U'), 0xFE, args.hue, args.sat, args.val])
    print(dev.read(8))

def do_info(dw, _, cliargs) :
  with dw as dev :
    print("Manufacturer: %s" % dev.get_manufacturer_string())
    print("Product: %s"      % dev.get_product_string())
    print("Serial No: %s"    % dev.get_serial_number_string())

    dev.write([0, ord('V')] + [0] * 7)
    r = dev.read(8)
    print("Build stamp: %02x%02x%02x%02x%02x" % (r[3], r[4], r[5], r[6], r[7]))

def do_raw(dw, _, cliargs) :
  if len(cliargs) > 8 :
    print("Refusing to send more than 8 bytes",file=sys.stderr)
    os.exit(1)

  vl = list(map(auto_int,cliargs))
  if any(map(lambda x : not (0x00 <= x <= 0xFF), vl)) :
   print("Invalid byte",file=sys.stderr)
   os.exit(1)

  with dw as dev :
    devwr(dev, vl)
    print(dev.read(8))

cmds = {
    "ledon" : do_leds_onoff,
    "ledoff" : do_leds_onoff,
    "allhsv" : do_all_hsv,
    "info" : do_info,
    "raw" : do_raw
}

argp = argparse.ArgumentParser(description="nwf's keyboard firmware tool")
argp.add_argument("--log-level", help="Set the logging level.  Defaults to CRITICAL",
                  choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"],
                  default="ERROR")
argp.add_argument("command", choices=cmds.keys())
argp.add_argument('remainder', nargs=argparse.REMAINDER)
args = argp.parse_args()

logging.basicConfig(level=logging.getLevelName(args.log_level), format="%(message)s")
cmds[args.command](HiddevWrapper(), args.command, args.remainder)
