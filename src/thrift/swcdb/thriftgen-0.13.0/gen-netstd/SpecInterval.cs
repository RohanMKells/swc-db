/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using Thrift;
using Thrift.Collections;

using Thrift.Protocol;
using Thrift.Protocol.Entities;
using Thrift.Protocol.Utilities;
using Thrift.Transport;
using Thrift.Transport.Client;
using Thrift.Transport.Server;
using Thrift.Processor;



/// <summary>
/// The Cells Interval Specifications with interval-scope Flags
/// </summary>
public partial class SpecInterval : TBase
{
  private List<byte[]> _range_begin;
  private List<byte[]> _range_end;
  private List<byte[]> _range_offset;
  private List<byte[]> _offset_key;
  private long _offset_rev;
  private List<SpecFraction> _key_start;
  private List<SpecFraction> _key_finish;
  private SpecValue _value;
  private SpecTimestamp _ts_start;
  private SpecTimestamp _ts_finish;
  private SpecFlags _flags;

  /// <summary>
  /// Begin of Ranges evaluation with this Key inclusive
  /// </summary>
  public List<byte[]> Range_begin
  {
    get
    {
      return _range_begin;
    }
    set
    {
      __isset.range_begin = true;
      this._range_begin = value;
    }
  }

  /// <summary>
  /// End of Ranges evaluation with this Key inclusive
  /// </summary>
  public List<byte[]> Range_end
  {
    get
    {
      return _range_end;
    }
    set
    {
      __isset.range_end = true;
      this._range_end = value;
    }
  }

  /// <summary>
  /// Offset of Ranges evaluation with this Key inclusive
  /// </summary>
  public List<byte[]> Range_offset
  {
    get
    {
      return _range_offset;
    }
    set
    {
      __isset.range_offset = true;
      this._range_offset = value;
    }
  }

  /// <summary>
  /// Offset Cell Key of a Scan, select cells from this key inclusive
  /// </summary>
  public List<byte[]> Offset_key
  {
    get
    {
      return _offset_key;
    }
    set
    {
      __isset.offset_key = true;
      this._offset_key = value;
    }
  }

  /// <summary>
  /// Offset Cell Timestamp of a Scan, select cells after this timestamp
  /// </summary>
  public long Offset_rev
  {
    get
    {
      return _offset_rev;
    }
    set
    {
      __isset.offset_rev = true;
      this._offset_rev = value;
    }
  }

  /// <summary>
  /// The Key Start Spec, the start of cells-interval key match
  /// </summary>
  public List<SpecFraction> Key_start
  {
    get
    {
      return _key_start;
    }
    set
    {
      __isset.key_start = true;
      this._key_start = value;
    }
  }

  /// <summary>
  /// The Key Finish Spec, the finish of cells-interval key match
  /// </summary>
  public List<SpecFraction> Key_finish
  {
    get
    {
      return _key_finish;
    }
    set
    {
      __isset.key_finish = true;
      this._key_finish = value;
    }
  }

  /// <summary>
  /// The Cell Value Spec, cell-value match
  /// </summary>
  public SpecValue Value
  {
    get
    {
      return _value;
    }
    set
    {
      __isset.@value = true;
      this._value = value;
    }
  }

  /// <summary>
  /// The Timestamp Start Spec, the start of cells-interval timestamp match
  /// </summary>
  public SpecTimestamp Ts_start
  {
    get
    {
      return _ts_start;
    }
    set
    {
      __isset.ts_start = true;
      this._ts_start = value;
    }
  }

  /// <summary>
  /// The Timestamp Finish Spec, the finish of cells-interval timestamp match
  /// </summary>
  public SpecTimestamp Ts_finish
  {
    get
    {
      return _ts_finish;
    }
    set
    {
      __isset.ts_finish = true;
      this._ts_finish = value;
    }
  }

  /// <summary>
  /// The Interval Flags Specification
  /// </summary>
  public SpecFlags Flags
  {
    get
    {
      return _flags;
    }
    set
    {
      __isset.flags = true;
      this._flags = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool range_begin;
    public bool range_end;
    public bool range_offset;
    public bool offset_key;
    public bool offset_rev;
    public bool key_start;
    public bool key_finish;
    public bool @value;
    public bool ts_start;
    public bool ts_finish;
    public bool flags;
  }

  public SpecInterval()
  {
  }

  public async Task ReadAsync(TProtocol iprot, CancellationToken cancellationToken)
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
            if (field.Type == TType.List)
            {
              {
                TList _list12 = await iprot.ReadListBeginAsync(cancellationToken);
                Range_begin = new List<byte[]>(_list12.Count);
                for(int _i13 = 0; _i13 < _list12.Count; ++_i13)
                {
                  byte[] _elem14;
                  _elem14 = await iprot.ReadBinaryAsync(cancellationToken);
                  Range_begin.Add(_elem14);
                }
                await iprot.ReadListEndAsync(cancellationToken);
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
                TList _list15 = await iprot.ReadListBeginAsync(cancellationToken);
                Range_end = new List<byte[]>(_list15.Count);
                for(int _i16 = 0; _i16 < _list15.Count; ++_i16)
                {
                  byte[] _elem17;
                  _elem17 = await iprot.ReadBinaryAsync(cancellationToken);
                  Range_end.Add(_elem17);
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
                TList _list18 = await iprot.ReadListBeginAsync(cancellationToken);
                Range_offset = new List<byte[]>(_list18.Count);
                for(int _i19 = 0; _i19 < _list18.Count; ++_i19)
                {
                  byte[] _elem20;
                  _elem20 = await iprot.ReadBinaryAsync(cancellationToken);
                  Range_offset.Add(_elem20);
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
                TList _list21 = await iprot.ReadListBeginAsync(cancellationToken);
                Offset_key = new List<byte[]>(_list21.Count);
                for(int _i22 = 0; _i22 < _list21.Count; ++_i22)
                {
                  byte[] _elem23;
                  _elem23 = await iprot.ReadBinaryAsync(cancellationToken);
                  Offset_key.Add(_elem23);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 5:
            if (field.Type == TType.I64)
            {
              Offset_rev = await iprot.ReadI64Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 6:
            if (field.Type == TType.List)
            {
              {
                TList _list24 = await iprot.ReadListBeginAsync(cancellationToken);
                Key_start = new List<SpecFraction>(_list24.Count);
                for(int _i25 = 0; _i25 < _list24.Count; ++_i25)
                {
                  SpecFraction _elem26;
                  _elem26 = new SpecFraction();
                  await _elem26.ReadAsync(iprot, cancellationToken);
                  Key_start.Add(_elem26);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 7:
            if (field.Type == TType.List)
            {
              {
                TList _list27 = await iprot.ReadListBeginAsync(cancellationToken);
                Key_finish = new List<SpecFraction>(_list27.Count);
                for(int _i28 = 0; _i28 < _list27.Count; ++_i28)
                {
                  SpecFraction _elem29;
                  _elem29 = new SpecFraction();
                  await _elem29.ReadAsync(iprot, cancellationToken);
                  Key_finish.Add(_elem29);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 8:
            if (field.Type == TType.Struct)
            {
              Value = new SpecValue();
              await Value.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 9:
            if (field.Type == TType.Struct)
            {
              Ts_start = new SpecTimestamp();
              await Ts_start.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 10:
            if (field.Type == TType.Struct)
            {
              Ts_finish = new SpecTimestamp();
              await Ts_finish.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 11:
            if (field.Type == TType.Struct)
            {
              Flags = new SpecFlags();
              await Flags.ReadAsync(iprot, cancellationToken);
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

  public async Task WriteAsync(TProtocol oprot, CancellationToken cancellationToken)
  {
    oprot.IncrementRecursionDepth();
    try
    {
      var struc = new TStruct("SpecInterval");
      await oprot.WriteStructBeginAsync(struc, cancellationToken);
      var field = new TField();
      if (Range_begin != null && __isset.range_begin)
      {
        field.Name = "range_begin";
        field.Type = TType.List;
        field.ID = 1;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.String, Range_begin.Count), cancellationToken);
          foreach (byte[] _iter30 in Range_begin)
          {
            await oprot.WriteBinaryAsync(_iter30, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Range_end != null && __isset.range_end)
      {
        field.Name = "range_end";
        field.Type = TType.List;
        field.ID = 2;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.String, Range_end.Count), cancellationToken);
          foreach (byte[] _iter31 in Range_end)
          {
            await oprot.WriteBinaryAsync(_iter31, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Range_offset != null && __isset.range_offset)
      {
        field.Name = "range_offset";
        field.Type = TType.List;
        field.ID = 3;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.String, Range_offset.Count), cancellationToken);
          foreach (byte[] _iter32 in Range_offset)
          {
            await oprot.WriteBinaryAsync(_iter32, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Offset_key != null && __isset.offset_key)
      {
        field.Name = "offset_key";
        field.Type = TType.List;
        field.ID = 4;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.String, Offset_key.Count), cancellationToken);
          foreach (byte[] _iter33 in Offset_key)
          {
            await oprot.WriteBinaryAsync(_iter33, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (__isset.offset_rev)
      {
        field.Name = "offset_rev";
        field.Type = TType.I64;
        field.ID = 5;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await oprot.WriteI64Async(Offset_rev, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Key_start != null && __isset.key_start)
      {
        field.Name = "key_start";
        field.Type = TType.List;
        field.ID = 6;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.Struct, Key_start.Count), cancellationToken);
          foreach (SpecFraction _iter34 in Key_start)
          {
            await _iter34.WriteAsync(oprot, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Key_finish != null && __isset.key_finish)
      {
        field.Name = "key_finish";
        field.Type = TType.List;
        field.ID = 7;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        {
          await oprot.WriteListBeginAsync(new TList(TType.Struct, Key_finish.Count), cancellationToken);
          foreach (SpecFraction _iter35 in Key_finish)
          {
            await _iter35.WriteAsync(oprot, cancellationToken);
          }
          await oprot.WriteListEndAsync(cancellationToken);
        }
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Value != null && __isset.@value)
      {
        field.Name = "value";
        field.Type = TType.Struct;
        field.ID = 8;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await Value.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Ts_start != null && __isset.ts_start)
      {
        field.Name = "ts_start";
        field.Type = TType.Struct;
        field.ID = 9;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await Ts_start.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Ts_finish != null && __isset.ts_finish)
      {
        field.Name = "ts_finish";
        field.Type = TType.Struct;
        field.ID = 10;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await Ts_finish.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if (Flags != null && __isset.flags)
      {
        field.Name = "flags";
        field.Type = TType.Struct;
        field.ID = 11;
        await oprot.WriteFieldBeginAsync(field, cancellationToken);
        await Flags.WriteAsync(oprot, cancellationToken);
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
    var other = that as SpecInterval;
    if (other == null) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.range_begin == other.__isset.range_begin) && ((!__isset.range_begin) || (System.Object.Equals(Range_begin, other.Range_begin))))
      && ((__isset.range_end == other.__isset.range_end) && ((!__isset.range_end) || (System.Object.Equals(Range_end, other.Range_end))))
      && ((__isset.range_offset == other.__isset.range_offset) && ((!__isset.range_offset) || (System.Object.Equals(Range_offset, other.Range_offset))))
      && ((__isset.offset_key == other.__isset.offset_key) && ((!__isset.offset_key) || (System.Object.Equals(Offset_key, other.Offset_key))))
      && ((__isset.offset_rev == other.__isset.offset_rev) && ((!__isset.offset_rev) || (System.Object.Equals(Offset_rev, other.Offset_rev))))
      && ((__isset.key_start == other.__isset.key_start) && ((!__isset.key_start) || (System.Object.Equals(Key_start, other.Key_start))))
      && ((__isset.key_finish == other.__isset.key_finish) && ((!__isset.key_finish) || (System.Object.Equals(Key_finish, other.Key_finish))))
      && ((__isset.@value == other.__isset.@value) && ((!__isset.@value) || (System.Object.Equals(Value, other.Value))))
      && ((__isset.ts_start == other.__isset.ts_start) && ((!__isset.ts_start) || (System.Object.Equals(Ts_start, other.Ts_start))))
      && ((__isset.ts_finish == other.__isset.ts_finish) && ((!__isset.ts_finish) || (System.Object.Equals(Ts_finish, other.Ts_finish))))
      && ((__isset.flags == other.__isset.flags) && ((!__isset.flags) || (System.Object.Equals(Flags, other.Flags))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.range_begin)
        hashcode = (hashcode * 397) + Range_begin.GetHashCode();
      if(__isset.range_end)
        hashcode = (hashcode * 397) + Range_end.GetHashCode();
      if(__isset.range_offset)
        hashcode = (hashcode * 397) + Range_offset.GetHashCode();
      if(__isset.offset_key)
        hashcode = (hashcode * 397) + Offset_key.GetHashCode();
      if(__isset.offset_rev)
        hashcode = (hashcode * 397) + Offset_rev.GetHashCode();
      if(__isset.key_start)
        hashcode = (hashcode * 397) + Key_start.GetHashCode();
      if(__isset.key_finish)
        hashcode = (hashcode * 397) + Key_finish.GetHashCode();
      if(__isset.@value)
        hashcode = (hashcode * 397) + Value.GetHashCode();
      if(__isset.ts_start)
        hashcode = (hashcode * 397) + Ts_start.GetHashCode();
      if(__isset.ts_finish)
        hashcode = (hashcode * 397) + Ts_finish.GetHashCode();
      if(__isset.flags)
        hashcode = (hashcode * 397) + Flags.GetHashCode();
    }
    return hashcode;
  }

  public override string ToString()
  {
    var sb = new StringBuilder("SpecInterval(");
    bool __first = true;
    if (Range_begin != null && __isset.range_begin)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Range_begin: ");
      sb.Append(Range_begin);
    }
    if (Range_end != null && __isset.range_end)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Range_end: ");
      sb.Append(Range_end);
    }
    if (Range_offset != null && __isset.range_offset)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Range_offset: ");
      sb.Append(Range_offset);
    }
    if (Offset_key != null && __isset.offset_key)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Offset_key: ");
      sb.Append(Offset_key);
    }
    if (__isset.offset_rev)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Offset_rev: ");
      sb.Append(Offset_rev);
    }
    if (Key_start != null && __isset.key_start)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Key_start: ");
      sb.Append(Key_start);
    }
    if (Key_finish != null && __isset.key_finish)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Key_finish: ");
      sb.Append(Key_finish);
    }
    if (Value != null && __isset.@value)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Value: ");
      sb.Append(Value== null ? "<null>" : Value.ToString());
    }
    if (Ts_start != null && __isset.ts_start)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Ts_start: ");
      sb.Append(Ts_start== null ? "<null>" : Ts_start.ToString());
    }
    if (Ts_finish != null && __isset.ts_finish)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Ts_finish: ");
      sb.Append(Ts_finish== null ? "<null>" : Ts_finish.ToString());
    }
    if (Flags != null && __isset.flags)
    {
      if(!__first) { sb.Append(", "); }
      __first = false;
      sb.Append("Flags: ");
      sb.Append(Flags== null ? "<null>" : Flags.ToString());
    }
    sb.Append(")");
    return sb.ToString();
  }
}

