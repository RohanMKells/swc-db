/**
 * <auto-generated>
 * Autogenerated by Thrift Compiler (0.17.0)
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 * </auto-generated>
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using Thrift;
using Thrift.Collections;
using Thrift.Protocol;
using Thrift.Protocol.Entities;
using Thrift.Protocol.Utilities;
using Thrift.Transport;
using Thrift.Transport.Client;
using Thrift.Transport.Server;
using Thrift.Processor;


#pragma warning disable IDE0079  // remove unnecessary pragmas
#pragma warning disable IDE0017  // object init can be simplified
#pragma warning disable IDE0028  // collection init can be simplified
#pragma warning disable IDE1006  // parts of the code use IDL spelling
#pragma warning disable CA1822   // empty DeepCopy() methods still non-static
#pragma warning disable IDE0083  // pattern matching "that is not SomeType" requires net5.0 but we still support earlier versions


/// <summary>
/// The Fraction Cells for results on Fraction of scan
/// </summary>
public partial class FCells : TBase
{
  private Dictionary<byte[], FCells> _f;
  private List<FCellPlain> _plain_cells;
  private List<FCellCounter> _counter_cells;
  private List<FCellSerial> _serial_cells;

  /// <summary>
  /// The Fraction Container for the Next Fractions Tree,  defined as FCells items in a map-container by current Fraction bytes
  /// </summary>
  public Dictionary<byte[], FCells> F
  {
    get
    {
      return _f;
    }
    set
    {
      __isset.f = true;
      this._f = value;
    }
  }

  /// <summary>
  /// The current Fraction's Cells, defined as FCellPlain items in a list-container
  /// </summary>
  public List<FCellPlain> Plain_cells
  {
    get
    {
      return _plain_cells;
    }
    set
    {
      __isset.plain_cells = true;
      this._plain_cells = value;
    }
  }

  /// <summary>
  /// The current Fraction's Cells, defined as FCellCounter items in a list-container
  /// </summary>
  public List<FCellCounter> Counter_cells
  {
    get
    {
      return _counter_cells;
    }
    set
    {
      __isset.counter_cells = true;
      this._counter_cells = value;
    }
  }

  /// <summary>
  /// The current Fraction's Serial Cells, defined as FCellSerial items in a list-container
  /// </summary>
  public List<FCellSerial> Serial_cells
  {
    get
    {
      return _serial_cells;
    }
    set
    {
      __isset.serial_cells = true;
      this._serial_cells = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool f;
    public bool plain_cells;
    public bool counter_cells;
    public bool serial_cells;
  }

  public FCells()
  {
  }

  public FCells DeepCopy()
  {
    var tmp536 = new FCells();
    if((F != null) && __isset.f)
    {
      tmp536.F = this.F.DeepCopy();
    }
    tmp536.__isset.f = this.__isset.f;
    if((Plain_cells != null) && __isset.plain_cells)
    {
      tmp536.Plain_cells = this.Plain_cells.DeepCopy();
    }
    tmp536.__isset.plain_cells = this.__isset.plain_cells;
    if((Counter_cells != null) && __isset.counter_cells)
    {
      tmp536.Counter_cells = this.Counter_cells.DeepCopy();
    }
    tmp536.__isset.counter_cells = this.__isset.counter_cells;
    if((Serial_cells != null) && __isset.serial_cells)
    {
      tmp536.Serial_cells = this.Serial_cells.DeepCopy();
    }
    tmp536.__isset.serial_cells = this.__isset.serial_cells;
    return tmp536;
  }

  public async global::System.Threading.Tasks.Task ReadAsync(TProtocol iprot, CancellationToken cancellationToken)
  {
    iprot.IncrementRecursionDepth();
    try
    {
      TField field;
      await iprot.ReadStructBeginAsync(cancellationToken);
      while (true)
      {
        field = await iprot.ReadFieldBeginAsync(cancellationToken);
        if (field.Type == TType.Stop)
        {
          break;
        }

        switch (field.ID)
        {
          case 1:
            if (field.Type == TType.Map)
            {
              {
                var _map537 = await iprot.ReadMapBeginAsync(cancellationToken);
                F = new Dictionary<byte[], FCells>(_map537.Count);
                for(int _i538 = 0; _i538 < _map537.Count; ++_i538)
                {
                  byte[] _key539;
                  FCells _val540;
                  _key539 = await iprot.ReadBinaryAsync(cancellationToken);
                  _val540 = new FCells();
                  await _val540.ReadAsync(iprot, cancellationToken);
                  F[_key539] = _val540;
                }
                await iprot.ReadMapEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 2:
            if (field.Type == TType.List)
            {
              {
                var _list541 = await iprot.ReadListBeginAsync(cancellationToken);
                Plain_cells = new List<FCellPlain>(_list541.Count);
                for(int _i542 = 0; _i542 < _list541.Count; ++_i542)
                {
                  FCellPlain _elem543;
                  _elem543 = new FCellPlain();
                  await _elem543.ReadAsync(iprot, cancellationToken);
                  Plain_cells.Add(_elem543);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 3:
            if (field.Type == TType.List)
            {
              {
                var _list544 = await iprot.ReadListBeginAsync(cancellationToken);
                Counter_cells = new List<FCellCounter>(_list544.Count);
                for(int _i545 = 0; _i545 < _list544.Count; ++_i545)
                {
                  FCellCounter _elem546;
                  _elem546 = new FCellCounter();
                  await _elem546.ReadAsync(iprot, cancellationToken);
                  Counter_cells.Add(_elem546);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 4:
            if (field.Type == TType.List)
            {
              {
                var _list547 = await iprot.ReadListBeginAsync(cancellationToken);
                Serial_cells = new List<FCellSerial>(_list547.Count);
                for(int _i548 = 0; _i548 < _list547.Count; ++_i548)
                {
                  FCellSerial _elem549;
                  _elem549 = new FCellSerial();
                  await _elem549.ReadAsync(iprot, cancellationToken);
                  Serial_cells.Add(_elem549);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          default: 
            await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            break;
        }

        await iprot.ReadFieldEndAsync(cancellationToken);
      }

      await iprot.ReadStructEndAsync(cancellationToken);
    }
    finally
    {
      iprot.DecrementRecursionDepth();
    }
  }

  public async global::System.Threading.Tasks.Task WriteAsync(TProtocol oprot, CancellationToken cancellationToken)
  {
    oprot.IncrementRecursionDepth();
    try
    {
      var tmp550 = new TStruct("FCells");
      await oprot.WriteStructBeginAsync(tmp550, cancellationToken);
      var tmp551 = new TField();
      if((F != null) && __isset.f)
      {
        tmp551.Name = "f";
        tmp551.Type = TType.Map;
        tmp551.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp551, cancellationToken);
        await oprot.WriteMapBeginAsync(new TMap(TType.String, TType.Struct, F.Count), cancellationToken);
        foreach (byte[] _iter552 in F.Keys)
        {
          await oprot.WriteBinaryAsync(_iter552, cancellationToken);
          await F[_iter552].WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteMapEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Plain_cells != null) && __isset.plain_cells)
      {
        tmp551.Name = "plain_cells";
        tmp551.Type = TType.List;
        tmp551.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp551, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Plain_cells.Count), cancellationToken);
        foreach (FCellPlain _iter553 in Plain_cells)
        {
          await _iter553.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Counter_cells != null) && __isset.counter_cells)
      {
        tmp551.Name = "counter_cells";
        tmp551.Type = TType.List;
        tmp551.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp551, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Counter_cells.Count), cancellationToken);
        foreach (FCellCounter _iter554 in Counter_cells)
        {
          await _iter554.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Serial_cells != null) && __isset.serial_cells)
      {
        tmp551.Name = "serial_cells";
        tmp551.Type = TType.List;
        tmp551.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp551, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Serial_cells.Count), cancellationToken);
        foreach (FCellSerial _iter555 in Serial_cells)
        {
          await _iter555.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      await oprot.WriteFieldStopAsync(cancellationToken);
      await oprot.WriteStructEndAsync(cancellationToken);
    }
    finally
    {
      oprot.DecrementRecursionDepth();
    }
  }

  public override bool Equals(object that)
  {
    if (!(that is FCells other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.f == other.__isset.f) && ((!__isset.f) || (TCollections.Equals(F, other.F))))
      && ((__isset.plain_cells == other.__isset.plain_cells) && ((!__isset.plain_cells) || (TCollections.Equals(Plain_cells, other.Plain_cells))))
      && ((__isset.counter_cells == other.__isset.counter_cells) && ((!__isset.counter_cells) || (TCollections.Equals(Counter_cells, other.Counter_cells))))
      && ((__isset.serial_cells == other.__isset.serial_cells) && ((!__isset.serial_cells) || (TCollections.Equals(Serial_cells, other.Serial_cells))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if((F != null) && __isset.f)
      {
        hashcode = (hashcode * 397) + TCollections.GetHashCode(F);
      }
      if((Plain_cells != null) && __isset.plain_cells)
      {
        hashcode = (hashcode * 397) + TCollections.GetHashCode(Plain_cells);
      }
      if((Counter_cells != null) && __isset.counter_cells)
      {
        hashcode = (hashcode * 397) + TCollections.GetHashCode(Counter_cells);
      }
      if((Serial_cells != null) && __isset.serial_cells)
      {
        hashcode = (hashcode * 397) + TCollections.GetHashCode(Serial_cells);
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp556 = new StringBuilder("FCells(");
    int tmp557 = 0;
    if((F != null) && __isset.f)
    {
      if(0 < tmp557++) { tmp556.Append(", "); }
      tmp556.Append("F: ");
      F.ToString(tmp556);
    }
    if((Plain_cells != null) && __isset.plain_cells)
    {
      if(0 < tmp557++) { tmp556.Append(", "); }
      tmp556.Append("Plain_cells: ");
      Plain_cells.ToString(tmp556);
    }
    if((Counter_cells != null) && __isset.counter_cells)
    {
      if(0 < tmp557++) { tmp556.Append(", "); }
      tmp556.Append("Counter_cells: ");
      Counter_cells.ToString(tmp556);
    }
    if((Serial_cells != null) && __isset.serial_cells)
    {
      if(0 < tmp557++) { tmp556.Append(", "); }
      tmp556.Append("Serial_cells: ");
      Serial_cells.ToString(tmp556);
    }
    tmp556.Append(')');
    return tmp556.ToString();
  }
}

