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
/// The Serial Values Cell field with Update Operation
/// </summary>
public partial class CellValueSerialOp : TBase
{
  private int _field_id;
  private FU_INT64 _v_int64;
  private FU_DOUBLE _v_double;
  private FU_BYTES _v_bytes;
  private List<byte[]> _v_key;
  private FU_LI _v_li;
  private FU_LB _v_lb;

  /// <summary>
  /// The Field ID, a single ID can have any/all the field types
  /// </summary>
  public int Field_id
  {
    get
    {
      return _field_id;
    }
    set
    {
      __isset.field_id = true;
      this._field_id = value;
    }
  }

  /// <summary>
  /// The INT64 type update-field
  /// </summary>
  public FU_INT64 V_int64
  {
    get
    {
      return _v_int64;
    }
    set
    {
      __isset.v_int64 = true;
      this._v_int64 = value;
    }
  }

  /// <summary>
  /// The DOUBLE type update-field
  /// </summary>
  public FU_DOUBLE V_double
  {
    get
    {
      return _v_double;
    }
    set
    {
      __isset.v_double = true;
      this._v_double = value;
    }
  }

  /// <summary>
  /// The BYTES type update-field
  /// </summary>
  public FU_BYTES V_bytes
  {
    get
    {
      return _v_bytes;
    }
    set
    {
      __isset.v_bytes = true;
      this._v_bytes = value;
    }
  }

  /// <summary>
  /// The Cell KEY type update-field
  /// </summary>
  public List<byte[]> V_key
  {
    get
    {
      return _v_key;
    }
    set
    {
      __isset.v_key = true;
      this._v_key = value;
    }
  }

  /// <summary>
  /// The LIST INT64 type update-field
  /// </summary>
  public FU_LI V_li
  {
    get
    {
      return _v_li;
    }
    set
    {
      __isset.v_li = true;
      this._v_li = value;
    }
  }

  /// <summary>
  /// The LIST BYTES type update-field
  /// </summary>
  public FU_LB V_lb
  {
    get
    {
      return _v_lb;
    }
    set
    {
      __isset.v_lb = true;
      this._v_lb = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool field_id;
    public bool v_int64;
    public bool v_double;
    public bool v_bytes;
    public bool v_key;
    public bool v_li;
    public bool v_lb;
  }

  public CellValueSerialOp()
  {
  }

  public CellValueSerialOp DeepCopy()
  {
    var tmp359 = new CellValueSerialOp();
    if(__isset.field_id)
    {
      tmp359.Field_id = this.Field_id;
    }
    tmp359.__isset.field_id = this.__isset.field_id;
    if((V_int64 != null) && __isset.v_int64)
    {
      tmp359.V_int64 = (FU_INT64)this.V_int64.DeepCopy();
    }
    tmp359.__isset.v_int64 = this.__isset.v_int64;
    if((V_double != null) && __isset.v_double)
    {
      tmp359.V_double = (FU_DOUBLE)this.V_double.DeepCopy();
    }
    tmp359.__isset.v_double = this.__isset.v_double;
    if((V_bytes != null) && __isset.v_bytes)
    {
      tmp359.V_bytes = (FU_BYTES)this.V_bytes.DeepCopy();
    }
    tmp359.__isset.v_bytes = this.__isset.v_bytes;
    if((V_key != null) && __isset.v_key)
    {
      tmp359.V_key = this.V_key.DeepCopy();
    }
    tmp359.__isset.v_key = this.__isset.v_key;
    if((V_li != null) && __isset.v_li)
    {
      tmp359.V_li = (FU_LI)this.V_li.DeepCopy();
    }
    tmp359.__isset.v_li = this.__isset.v_li;
    if((V_lb != null) && __isset.v_lb)
    {
      tmp359.V_lb = (FU_LB)this.V_lb.DeepCopy();
    }
    tmp359.__isset.v_lb = this.__isset.v_lb;
    return tmp359;
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
            if (field.Type == TType.I32)
            {
              Field_id = await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 2:
            if (field.Type == TType.Struct)
            {
              V_int64 = new FU_INT64();
              await V_int64.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 3:
            if (field.Type == TType.Struct)
            {
              V_double = new FU_DOUBLE();
              await V_double.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 4:
            if (field.Type == TType.Struct)
            {
              V_bytes = new FU_BYTES();
              await V_bytes.ReadAsync(iprot, cancellationToken);
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
                var _list360 = await iprot.ReadListBeginAsync(cancellationToken);
                V_key = new List<byte[]>(_list360.Count);
                for(int _i361 = 0; _i361 < _list360.Count; ++_i361)
                {
                  byte[] _elem362;
                  _elem362 = await iprot.ReadBinaryAsync(cancellationToken);
                  V_key.Add(_elem362);
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
            if (field.Type == TType.Struct)
            {
              V_li = new FU_LI();
              await V_li.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 7:
            if (field.Type == TType.Struct)
            {
              V_lb = new FU_LB();
              await V_lb.ReadAsync(iprot, cancellationToken);
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
      var tmp363 = new TStruct("CellValueSerialOp");
      await oprot.WriteStructBeginAsync(tmp363, cancellationToken);
      var tmp364 = new TField();
      if(__isset.field_id)
      {
        tmp364.Name = "field_id";
        tmp364.Type = TType.I32;
        tmp364.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp364, cancellationToken);
        await oprot.WriteI32Async(Field_id, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V_int64 != null) && __isset.v_int64)
      {
        tmp364.Name = "v_int64";
        tmp364.Type = TType.Struct;
        tmp364.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp364, cancellationToken);
        await V_int64.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V_double != null) && __isset.v_double)
      {
        tmp364.Name = "v_double";
        tmp364.Type = TType.Struct;
        tmp364.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp364, cancellationToken);
        await V_double.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V_bytes != null) && __isset.v_bytes)
      {
        tmp364.Name = "v_bytes";
        tmp364.Type = TType.Struct;
        tmp364.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp364, cancellationToken);
        await V_bytes.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V_key != null) && __isset.v_key)
      {
        tmp364.Name = "v_key";
        tmp364.Type = TType.List;
        tmp364.ID = 5;
        await oprot.WriteFieldBeginAsync(tmp364, cancellationToken);
        await oprot.WriteListBeginAsync(new TList(TType.String, V_key.Count), cancellationToken);
        foreach (byte[] _iter365 in V_key)
        {
          await oprot.WriteBinaryAsync(_iter365, cancellationToken);
        }
        await oprot.WriteListEndAsync(cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V_li != null) && __isset.v_li)
      {
        tmp364.Name = "v_li";
        tmp364.Type = TType.Struct;
        tmp364.ID = 6;
        await oprot.WriteFieldBeginAsync(tmp364, cancellationToken);
        await V_li.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V_lb != null) && __isset.v_lb)
      {
        tmp364.Name = "v_lb";
        tmp364.Type = TType.Struct;
        tmp364.ID = 7;
        await oprot.WriteFieldBeginAsync(tmp364, cancellationToken);
        await V_lb.WriteAsync(oprot, cancellationToken);
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
    if (!(that is CellValueSerialOp other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.field_id == other.__isset.field_id) && ((!__isset.field_id) || (global::System.Object.Equals(Field_id, other.Field_id))))
      && ((__isset.v_int64 == other.__isset.v_int64) && ((!__isset.v_int64) || (global::System.Object.Equals(V_int64, other.V_int64))))
      && ((__isset.v_double == other.__isset.v_double) && ((!__isset.v_double) || (global::System.Object.Equals(V_double, other.V_double))))
      && ((__isset.v_bytes == other.__isset.v_bytes) && ((!__isset.v_bytes) || (global::System.Object.Equals(V_bytes, other.V_bytes))))
      && ((__isset.v_key == other.__isset.v_key) && ((!__isset.v_key) || (global::System.Object.Equals(V_key, other.V_key))))
      && ((__isset.v_li == other.__isset.v_li) && ((!__isset.v_li) || (global::System.Object.Equals(V_li, other.V_li))))
      && ((__isset.v_lb == other.__isset.v_lb) && ((!__isset.v_lb) || (global::System.Object.Equals(V_lb, other.V_lb))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.field_id)
      {
        hashcode = (hashcode * 397) + Field_id.GetHashCode();
      }
      if((V_int64 != null) && __isset.v_int64)
      {
        hashcode = (hashcode * 397) + V_int64.GetHashCode();
      }
      if((V_double != null) && __isset.v_double)
      {
        hashcode = (hashcode * 397) + V_double.GetHashCode();
      }
      if((V_bytes != null) && __isset.v_bytes)
      {
        hashcode = (hashcode * 397) + V_bytes.GetHashCode();
      }
      if((V_key != null) && __isset.v_key)
      {
        hashcode = (hashcode * 397) + V_key.GetHashCode();
      }
      if((V_li != null) && __isset.v_li)
      {
        hashcode = (hashcode * 397) + V_li.GetHashCode();
      }
      if((V_lb != null) && __isset.v_lb)
      {
        hashcode = (hashcode * 397) + V_lb.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp366 = new StringBuilder("CellValueSerialOp(");
    int tmp367 = 0;
    if(__isset.field_id)
    {
      if(0 < tmp367++) { tmp366.Append(", "); }
      tmp366.Append("Field_id: ");
      Field_id.ToString(tmp366);
    }
    if((V_int64 != null) && __isset.v_int64)
    {
      if(0 < tmp367++) { tmp366.Append(", "); }
      tmp366.Append("V_int64: ");
      V_int64.ToString(tmp366);
    }
    if((V_double != null) && __isset.v_double)
    {
      if(0 < tmp367++) { tmp366.Append(", "); }
      tmp366.Append("V_double: ");
      V_double.ToString(tmp366);
    }
    if((V_bytes != null) && __isset.v_bytes)
    {
      if(0 < tmp367++) { tmp366.Append(", "); }
      tmp366.Append("V_bytes: ");
      V_bytes.ToString(tmp366);
    }
    if((V_key != null) && __isset.v_key)
    {
      if(0 < tmp367++) { tmp366.Append(", "); }
      tmp366.Append("V_key: ");
      V_key.ToString(tmp366);
    }
    if((V_li != null) && __isset.v_li)
    {
      if(0 < tmp367++) { tmp366.Append(", "); }
      tmp366.Append("V_li: ");
      V_li.ToString(tmp366);
    }
    if((V_lb != null) && __isset.v_lb)
    {
      if(0 < tmp367++) { tmp366.Append(", "); }
      tmp366.Append("V_lb: ");
      V_lb.ToString(tmp366);
    }
    tmp366.Append(')');
    return tmp366.ToString();
  }
}

