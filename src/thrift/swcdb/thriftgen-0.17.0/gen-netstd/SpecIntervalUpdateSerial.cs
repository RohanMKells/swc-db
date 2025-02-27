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
/// The Value specs for an Updating Interval of 'updating' in SpecIntervalSerial
/// </summary>
public partial class SpecIntervalUpdateSerial : TBase
{
  private long _ts;
  private List<CellValueSerial> _v;
  private List<CellValueSerialOp> _v_op;
  private EncodingType _encoder;
  private SpecUpdateOP _update_op;

  /// <summary>
  /// The timestamp for the updated cell NULL: MIN_INT64-1, AUTO:MIN_INT64-1
  /// </summary>
  public long Ts
  {
    get
    {
      return _ts;
    }
    set
    {
      __isset.ts = true;
      this._ts = value;
    }
  }

  /// <summary>
  /// The values of serial-fields for the updated cell
  /// </summary>
  public List<CellValueSerial> V
  {
    get
    {
      return _v;
    }
    set
    {
      __isset.v = true;
      this._v = value;
    }
  }

  /// <summary>
  /// The values of serial-fields for the the SERIAL operation update
  /// </summary>
  public List<CellValueSerialOp> V_op
  {
    get
    {
      return _v_op;
    }
    set
    {
      __isset.v_op = true;
      this._v_op = value;
    }
  }

  /// <summary>
  /// Optionally the Cell Value Encoding Type: ZLIB/SNAPPY/ZSTD
  /// 
  /// <seealso cref="global::.EncodingType"/>
  /// </summary>
  public EncodingType Encoder
  {
    get
    {
      return _encoder;
    }
    set
    {
      __isset.encoder = true;
      this._encoder = value;
    }
  }

  /// <summary>
  /// Optionally the operaton of value update
  /// </summary>
  public SpecUpdateOP Update_op
  {
    get
    {
      return _update_op;
    }
    set
    {
      __isset.update_op = true;
      this._update_op = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool ts;
    public bool v;
    public bool v_op;
    public bool encoder;
    public bool update_op;
  }

  public SpecIntervalUpdateSerial()
  {
  }

  public SpecIntervalUpdateSerial DeepCopy()
  {
    var tmp70 = new SpecIntervalUpdateSerial();
    if(__isset.ts)
    {
      tmp70.Ts = this.Ts;
    }
    tmp70.__isset.ts = this.__isset.ts;
    if((V != null) && __isset.v)
    {
      tmp70.V = this.V.DeepCopy();
    }
    tmp70.__isset.v = this.__isset.v;
    if((V_op != null) && __isset.v_op)
    {
      tmp70.V_op = this.V_op.DeepCopy();
    }
    tmp70.__isset.v_op = this.__isset.v_op;
    if(__isset.encoder)
    {
      tmp70.Encoder = this.Encoder;
    }
    tmp70.__isset.encoder = this.__isset.encoder;
    if((Update_op != null) && __isset.update_op)
    {
      tmp70.Update_op = (SpecUpdateOP)this.Update_op.DeepCopy();
    }
    tmp70.__isset.update_op = this.__isset.update_op;
    return tmp70;
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
            if (field.Type == TType.I64)
            {
              Ts = await iprot.ReadI64Async(cancellationToken);
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
                var _list71 = await iprot.ReadListBeginAsync(cancellationToken);
                V = new List<CellValueSerial>(_list71.Count);
                for(int _i72 = 0; _i72 < _list71.Count; ++_i72)
                {
                  CellValueSerial _elem73;
                  _elem73 = new CellValueSerial();
                  await _elem73.ReadAsync(iprot, cancellationToken);
                  V.Add(_elem73);
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
                var _list74 = await iprot.ReadListBeginAsync(cancellationToken);
                V_op = new List<CellValueSerialOp>(_list74.Count);
                for(int _i75 = 0; _i75 < _list74.Count; ++_i75)
                {
                  CellValueSerialOp _elem76;
                  _elem76 = new CellValueSerialOp();
                  await _elem76.ReadAsync(iprot, cancellationToken);
                  V_op.Add(_elem76);
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
            if (field.Type == TType.I32)
            {
              Encoder = (EncodingType)await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 5:
            if (field.Type == TType.Struct)
            {
              Update_op = new SpecUpdateOP();
              await Update_op.ReadAsync(iprot, cancellationToken);
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
      var tmp77 = new TStruct("SpecIntervalUpdateSerial");
      await oprot.WriteStructBeginAsync(tmp77, cancellationToken);
      var tmp78 = new TField();
      if(__isset.ts)
      {
        tmp78.Name = "ts";
        tmp78.Type = TType.I64;
        tmp78.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp78, cancellationToken);
        await oprot.WriteI64Async(Ts, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V != null) && __isset.v)
      {
        tmp78.Name = "v";
        tmp78.Type = TType.List;
        tmp78.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp78, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, V.Count), cancellationToken);
        foreach (CellValueSerial _iter79 in V)
        {
          await _iter79.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V_op != null) && __isset.v_op)
      {
        tmp78.Name = "v_op";
        tmp78.Type = TType.List;
        tmp78.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp78, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.Struct, V_op.Count), cancellationToken);
        foreach (CellValueSerialOp _iter80 in V_op)
        {
          await _iter80.WriteAsync(oprot, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.encoder)
      {
        tmp78.Name = "encoder";
        tmp78.Type = TType.I32;
        tmp78.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp78, cancellationToken);
        await oprot.WriteI32Async((int)Encoder, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Update_op != null) && __isset.update_op)
      {
        tmp78.Name = "update_op";
        tmp78.Type = TType.Struct;
        tmp78.ID = 5;
        await oprot.WriteFieldBeginAsync(tmp78, cancellationToken);
        await Update_op.WriteAsync(oprot, cancellationToken);
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
    if (!(that is SpecIntervalUpdateSerial other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.ts == other.__isset.ts) && ((!__isset.ts) || (global::System.Object.Equals(Ts, other.Ts))))
      && ((__isset.v == other.__isset.v) && ((!__isset.v) || (global::System.Object.Equals(V, other.V))))
      && ((__isset.v_op == other.__isset.v_op) && ((!__isset.v_op) || (global::System.Object.Equals(V_op, other.V_op))))
      && ((__isset.encoder == other.__isset.encoder) && ((!__isset.encoder) || (global::System.Object.Equals(Encoder, other.Encoder))))
      && ((__isset.update_op == other.__isset.update_op) && ((!__isset.update_op) || (global::System.Object.Equals(Update_op, other.Update_op))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.ts)
      {
        hashcode = (hashcode * 397) + Ts.GetHashCode();
      }
      if((V != null) && __isset.v)
      {
        hashcode = (hashcode * 397) + V.GetHashCode();
      }
      if((V_op != null) && __isset.v_op)
      {
        hashcode = (hashcode * 397) + V_op.GetHashCode();
      }
      if(__isset.encoder)
      {
        hashcode = (hashcode * 397) + Encoder.GetHashCode();
      }
      if((Update_op != null) && __isset.update_op)
      {
        hashcode = (hashcode * 397) + Update_op.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp81 = new StringBuilder("SpecIntervalUpdateSerial(");
    int tmp82 = 0;
    if(__isset.ts)
    {
      if(0 < tmp82++) { tmp81.Append(", "); }
      tmp81.Append("Ts: ");
      Ts.ToString(tmp81);
    }
    if((V != null) && __isset.v)
    {
      if(0 < tmp82++) { tmp81.Append(", "); }
      tmp81.Append("V: ");
      V.ToString(tmp81);
    }
    if((V_op != null) && __isset.v_op)
    {
      if(0 < tmp82++) { tmp81.Append(", "); }
      tmp81.Append("V_op: ");
      V_op.ToString(tmp81);
    }
    if(__isset.encoder)
    {
      if(0 < tmp82++) { tmp81.Append(", "); }
      tmp81.Append("Encoder: ");
      Encoder.ToString(tmp81);
    }
    if((Update_op != null) && __isset.update_op)
    {
      if(0 < tmp82++) { tmp81.Append(", "); }
      tmp81.Append("Update_op: ");
      Update_op.ToString(tmp81);
    }
    tmp81.Append(')');
    return tmp81.ToString();
  }
}

