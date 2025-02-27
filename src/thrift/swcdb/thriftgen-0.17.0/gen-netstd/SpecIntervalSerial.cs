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
/// The Cells Interval Serial type Specifications with interval-scope Flags
/// </summary>
public partial class SpecIntervalSerial : TBase
{
  private List<byte[]> _range_begin;
  private List<byte[]> _range_end;
  private List<byte[]> _offset_key;
  private long _offset_rev;
  private List<SpecKeyInterval> _key_intervals;
  private List<SpecValueSerial> _values;
  private SpecTimestamp _ts_start;
  private SpecTimestamp _ts_finish;
  private SpecFlags _flags;
  private SpecIntervalOptions _options;
  private SpecIntervalUpdateSerial _updating;

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
  /// The Key Intervals
  /// </summary>
  public List<SpecKeyInterval> Key_intervals
  {
    get
    {
      return _key_intervals;
    }
    set
    {
      __isset.key_intervals = true;
      this._key_intervals = value;
    }
  }

  /// <summary>
  /// The Serial Cell Value Specifications, cell-value fields match
  /// </summary>
  public List<SpecValueSerial> Values
  {
    get
    {
      return _values;
    }
    set
    {
      __isset.values = true;
      this._values = value;
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

  /// <summary>
  /// The Interval Options Specification
  /// 
  /// <seealso cref="global::.SpecIntervalOptions"/>
  /// </summary>
  public SpecIntervalOptions Options
  {
    get
    {
      return _options;
    }
    set
    {
      __isset.options = true;
      this._options = value;
    }
  }

  /// <summary>
  /// The Serial-Value spec of an Updating Interval
  /// </summary>
  public SpecIntervalUpdateSerial Updating
  {
    get
    {
      return _updating;
    }
    set
    {
      __isset.updating = true;
      this._updating = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool range_begin;
    public bool range_end;
    public bool offset_key;
    public bool offset_rev;
    public bool key_intervals;
    public bool values;
    public bool ts_start;
    public bool ts_finish;
    public bool flags;
    public bool options;
    public bool updating;
  }

  public SpecIntervalSerial()
  {
  }

  public SpecIntervalSerial DeepCopy()
  {
    var tmp222 = new SpecIntervalSerial();
    if((Range_begin != null) && __isset.range_begin)
    {
      tmp222.Range_begin = this.Range_begin.DeepCopy();
    }
    tmp222.__isset.range_begin = this.__isset.range_begin;
    if((Range_end != null) && __isset.range_end)
    {
      tmp222.Range_end = this.Range_end.DeepCopy();
    }
    tmp222.__isset.range_end = this.__isset.range_end;
    if((Offset_key != null) && __isset.offset_key)
    {
      tmp222.Offset_key = this.Offset_key.DeepCopy();
    }
    tmp222.__isset.offset_key = this.__isset.offset_key;
    if(__isset.offset_rev)
    {
      tmp222.Offset_rev = this.Offset_rev;
    }
    tmp222.__isset.offset_rev = this.__isset.offset_rev;
    if((Key_intervals != null) && __isset.key_intervals)
    {
      tmp222.Key_intervals = this.Key_intervals.DeepCopy();
    }
    tmp222.__isset.key_intervals = this.__isset.key_intervals;
    if((Values != null) && __isset.values)
    {
      tmp222.Values = this.Values.DeepCopy();
    }
    tmp222.__isset.values = this.__isset.values;
    if((Ts_start != null) && __isset.ts_start)
    {
      tmp222.Ts_start = (SpecTimestamp)this.Ts_start.DeepCopy();
    }
    tmp222.__isset.ts_start = this.__isset.ts_start;
    if((Ts_finish != null) && __isset.ts_finish)
    {
      tmp222.Ts_finish = (SpecTimestamp)this.Ts_finish.DeepCopy();
    }
    tmp222.__isset.ts_finish = this.__isset.ts_finish;
    if((Flags != null) && __isset.flags)
    {
      tmp222.Flags = (SpecFlags)this.Flags.DeepCopy();
    }
    tmp222.__isset.flags = this.__isset.flags;
    if(__isset.options)
    {
      tmp222.Options = this.Options;
    }
    tmp222.__isset.options = this.__isset.options;
    if((Updating != null) && __isset.updating)
    {
      tmp222.Updating = (SpecIntervalUpdateSerial)this.Updating.DeepCopy();
    }
    tmp222.__isset.updating = this.__isset.updating;
    return tmp222;
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
            if (field.Type == TType.List)
            {
              {
                var _list223 = await iprot.ReadListBeginAsync(cancellationToken);
                Range_begin = new List<byte[]>(_list223.Count);
                for(int _i224 = 0; _i224 < _list223.Count; ++_i224)
                {
                  byte[] _elem225;
                  _elem225 = await iprot.ReadBinaryAsync(cancellationToken);
                  Range_begin.Add(_elem225);
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
                var _list226 = await iprot.ReadListBeginAsync(cancellationToken);
                Range_end = new List<byte[]>(_list226.Count);
                for(int _i227 = 0; _i227 < _list226.Count; ++_i227)
                {
                  byte[] _elem228;
                  _elem228 = await iprot.ReadBinaryAsync(cancellationToken);
                  Range_end.Add(_elem228);
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
                var _list229 = await iprot.ReadListBeginAsync(cancellationToken);
                Offset_key = new List<byte[]>(_list229.Count);
                for(int _i230 = 0; _i230 < _list229.Count; ++_i230)
                {
                  byte[] _elem231;
                  _elem231 = await iprot.ReadBinaryAsync(cancellationToken);
                  Offset_key.Add(_elem231);
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
            if (field.Type == TType.I64)
            {
              Offset_rev = await iprot.ReadI64Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 5:
            if (field.Type == TType.List)
            {
              {
                var _list232 = await iprot.ReadListBeginAsync(cancellationToken);
                Key_intervals = new List<SpecKeyInterval>(_list232.Count);
                for(int _i233 = 0; _i233 < _list232.Count; ++_i233)
                {
                  SpecKeyInterval _elem234;
                  _elem234 = new SpecKeyInterval();
                  await _elem234.ReadAsync(iprot, cancellationToken);
                  Key_intervals.Add(_elem234);
                }
                await iprot.ReadListEndAsync(cancellationToken);
              }
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
                var _list235 = await iprot.ReadListBeginAsync(cancellationToken);
                Values = new List<SpecValueSerial>(_list235.Count);
                for(int _i236 = 0; _i236 < _list235.Count; ++_i236)
                {
                  SpecValueSerial _elem237;
                  _elem237 = new SpecValueSerial();
                  await _elem237.ReadAsync(iprot, cancellationToken);
                  Values.Add(_elem237);
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
          case 8:
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
          case 9:
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
          case 10:
            if (field.Type == TType.I32)
            {
              Options = (SpecIntervalOptions)await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 11:
            if (field.Type == TType.Struct)
            {
              Updating = new SpecIntervalUpdateSerial();
              await Updating.ReadAsync(iprot, cancellationToken);
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
      var tmp238 = new TStruct("SpecIntervalSerial");
      await oprot.WriteStructBeginAsync(tmp238, cancellationToken);
      var tmp239 = new TField();
      if((Range_begin != null) && __isset.range_begin)
      {
        tmp239.Name = "range_begin";
        tmp239.Type = TType.List;
        tmp239.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.String, Range_begin.Count), cancellationToken);
        foreach (byte[] _iter240 in Range_begin)
        {
          await oprot.WriteBinaryAsync(_iter240, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Range_end != null) && __isset.range_end)
      {
        tmp239.Name = "range_end";
        tmp239.Type = TType.List;
        tmp239.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.String, Range_end.Count), cancellationToken);
        foreach (byte[] _iter241 in Range_end)
        {
          await oprot.WriteBinaryAsync(_iter241, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Offset_key != null) && __isset.offset_key)
      {
        tmp239.Name = "offset_key";
        tmp239.Type = TType.List;
        tmp239.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.String, Offset_key.Count), cancellationToken);
        foreach (byte[] _iter242 in Offset_key)
        {
          await oprot.WriteBinaryAsync(_iter242, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.offset_rev)
      {
        tmp239.Name = "offset_rev";
        tmp239.Type = TType.I64;
        tmp239.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await oprot.WriteI64Async(Offset_rev, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Key_intervals != null) && __isset.key_intervals)
      {
        tmp239.Name = "key_intervals";
        tmp239.Type = TType.List;
        tmp239.ID = 5;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Key_intervals.Count), cancellationToken);
        foreach (SpecKeyInterval _iter243 in Key_intervals)
        {
          await _iter243.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Values != null) && __isset.values)
      {
        tmp239.Name = "values";
        tmp239.Type = TType.List;
        tmp239.ID = 6;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, Values.Count), cancellationToken);
        foreach (SpecValueSerial _iter244 in Values)
        {
          await _iter244.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Ts_start != null) && __isset.ts_start)
      {
        tmp239.Name = "ts_start";
        tmp239.Type = TType.Struct;
        tmp239.ID = 7;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await Ts_start.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Ts_finish != null) && __isset.ts_finish)
      {
        tmp239.Name = "ts_finish";
        tmp239.Type = TType.Struct;
        tmp239.ID = 8;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await Ts_finish.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Flags != null) && __isset.flags)
      {
        tmp239.Name = "flags";
        tmp239.Type = TType.Struct;
        tmp239.ID = 9;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await Flags.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.options)
      {
        tmp239.Name = "options";
        tmp239.Type = TType.I32;
        tmp239.ID = 10;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await oprot.WriteI32Async((int)Options, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Updating != null) && __isset.updating)
      {
        tmp239.Name = "updating";
        tmp239.Type = TType.Struct;
        tmp239.ID = 11;
        await oprot.WriteFieldBeginAsync(tmp239, cancellationToken);
        await Updating.WriteAsync(oprot, cancellationToken);
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
    if (!(that is SpecIntervalSerial other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.range_begin == other.__isset.range_begin) && ((!__isset.range_begin) || (global::System.Object.Equals(Range_begin, other.Range_begin))))
      && ((__isset.range_end == other.__isset.range_end) && ((!__isset.range_end) || (global::System.Object.Equals(Range_end, other.Range_end))))
      && ((__isset.offset_key == other.__isset.offset_key) && ((!__isset.offset_key) || (global::System.Object.Equals(Offset_key, other.Offset_key))))
      && ((__isset.offset_rev == other.__isset.offset_rev) && ((!__isset.offset_rev) || (global::System.Object.Equals(Offset_rev, other.Offset_rev))))
      && ((__isset.key_intervals == other.__isset.key_intervals) && ((!__isset.key_intervals) || (global::System.Object.Equals(Key_intervals, other.Key_intervals))))
      && ((__isset.values == other.__isset.values) && ((!__isset.values) || (global::System.Object.Equals(Values, other.Values))))
      && ((__isset.ts_start == other.__isset.ts_start) && ((!__isset.ts_start) || (global::System.Object.Equals(Ts_start, other.Ts_start))))
      && ((__isset.ts_finish == other.__isset.ts_finish) && ((!__isset.ts_finish) || (global::System.Object.Equals(Ts_finish, other.Ts_finish))))
      && ((__isset.flags == other.__isset.flags) && ((!__isset.flags) || (global::System.Object.Equals(Flags, other.Flags))))
      && ((__isset.options == other.__isset.options) && ((!__isset.options) || (global::System.Object.Equals(Options, other.Options))))
      && ((__isset.updating == other.__isset.updating) && ((!__isset.updating) || (global::System.Object.Equals(Updating, other.Updating))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if((Range_begin != null) && __isset.range_begin)
      {
        hashcode = (hashcode * 397) + Range_begin.GetHashCode();
      }
      if((Range_end != null) && __isset.range_end)
      {
        hashcode = (hashcode * 397) + Range_end.GetHashCode();
      }
      if((Offset_key != null) && __isset.offset_key)
      {
        hashcode = (hashcode * 397) + Offset_key.GetHashCode();
      }
      if(__isset.offset_rev)
      {
        hashcode = (hashcode * 397) + Offset_rev.GetHashCode();
      }
      if((Key_intervals != null) && __isset.key_intervals)
      {
        hashcode = (hashcode * 397) + Key_intervals.GetHashCode();
      }
      if((Values != null) && __isset.values)
      {
        hashcode = (hashcode * 397) + Values.GetHashCode();
      }
      if((Ts_start != null) && __isset.ts_start)
      {
        hashcode = (hashcode * 397) + Ts_start.GetHashCode();
      }
      if((Ts_finish != null) && __isset.ts_finish)
      {
        hashcode = (hashcode * 397) + Ts_finish.GetHashCode();
      }
      if((Flags != null) && __isset.flags)
      {
        hashcode = (hashcode * 397) + Flags.GetHashCode();
      }
      if(__isset.options)
      {
        hashcode = (hashcode * 397) + Options.GetHashCode();
      }
      if((Updating != null) && __isset.updating)
      {
        hashcode = (hashcode * 397) + Updating.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp245 = new StringBuilder("SpecIntervalSerial(");
    int tmp246 = 0;
    if((Range_begin != null) && __isset.range_begin)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Range_begin: ");
      Range_begin.ToString(tmp245);
    }
    if((Range_end != null) && __isset.range_end)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Range_end: ");
      Range_end.ToString(tmp245);
    }
    if((Offset_key != null) && __isset.offset_key)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Offset_key: ");
      Offset_key.ToString(tmp245);
    }
    if(__isset.offset_rev)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Offset_rev: ");
      Offset_rev.ToString(tmp245);
    }
    if((Key_intervals != null) && __isset.key_intervals)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Key_intervals: ");
      Key_intervals.ToString(tmp245);
    }
    if((Values != null) && __isset.values)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Values: ");
      Values.ToString(tmp245);
    }
    if((Ts_start != null) && __isset.ts_start)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Ts_start: ");
      Ts_start.ToString(tmp245);
    }
    if((Ts_finish != null) && __isset.ts_finish)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Ts_finish: ");
      Ts_finish.ToString(tmp245);
    }
    if((Flags != null) && __isset.flags)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Flags: ");
      Flags.ToString(tmp245);
    }
    if(__isset.options)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Options: ");
      Options.ToString(tmp245);
    }
    if((Updating != null) && __isset.updating)
    {
      if(0 < tmp246++) { tmp245.Append(", "); }
      tmp245.Append("Updating: ");
      Updating.ToString(tmp245);
    }
    tmp245.Append(')');
    return tmp245.ToString();
  }
}

