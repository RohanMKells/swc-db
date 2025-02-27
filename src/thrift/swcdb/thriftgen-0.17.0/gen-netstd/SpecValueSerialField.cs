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


public partial class SpecValueSerialField : TBase
{
  private int _field_id;
  private SpecValueSerial_INT64 _spec_int64;
  private SpecValueSerial_DOUBLE _spec_double;
  private SpecValueSerial_BYTES _spec_bytes;
  private SpecValueSerial_KEY _spec_key;
  private SpecValueSerial_LI _spec_li;
  private SpecValueSerial_LB _spec_lb;

  /// <summary>
  /// The Field Id of the Value Field
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
  /// The specifications of Int64 for the field
  /// </summary>
  public SpecValueSerial_INT64 Spec_int64
  {
    get
    {
      return _spec_int64;
    }
    set
    {
      __isset.spec_int64 = true;
      this._spec_int64 = value;
    }
  }

  /// <summary>
  /// The specifications of Double for the field
  /// </summary>
  public SpecValueSerial_DOUBLE Spec_double
  {
    get
    {
      return _spec_double;
    }
    set
    {
      __isset.spec_double = true;
      this._spec_double = value;
    }
  }

  /// <summary>
  /// The specifications of Bytes for the field
  /// </summary>
  public SpecValueSerial_BYTES Spec_bytes
  {
    get
    {
      return _spec_bytes;
    }
    set
    {
      __isset.spec_bytes = true;
      this._spec_bytes = value;
    }
  }

  /// <summary>
  /// The specifications of Cell-Key for the field
  /// </summary>
  public SpecValueSerial_KEY Spec_key
  {
    get
    {
      return _spec_key;
    }
    set
    {
      __isset.spec_key = true;
      this._spec_key = value;
    }
  }

  /// <summary>
  /// The specifications of List Int64 for the field
  /// </summary>
  public SpecValueSerial_LI Spec_li
  {
    get
    {
      return _spec_li;
    }
    set
    {
      __isset.spec_li = true;
      this._spec_li = value;
    }
  }

  /// <summary>
  /// The specifications of List Bytes for the field
  /// </summary>
  public SpecValueSerial_LB Spec_lb
  {
    get
    {
      return _spec_lb;
    }
    set
    {
      __isset.spec_lb = true;
      this._spec_lb = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool field_id;
    public bool spec_int64;
    public bool spec_double;
    public bool spec_bytes;
    public bool spec_key;
    public bool spec_li;
    public bool spec_lb;
  }

  public SpecValueSerialField()
  {
  }

  public SpecValueSerialField DeepCopy()
  {
    var tmp125 = new SpecValueSerialField();
    if(__isset.field_id)
    {
      tmp125.Field_id = this.Field_id;
    }
    tmp125.__isset.field_id = this.__isset.field_id;
    if((Spec_int64 != null) && __isset.spec_int64)
    {
      tmp125.Spec_int64 = (SpecValueSerial_INT64)this.Spec_int64.DeepCopy();
    }
    tmp125.__isset.spec_int64 = this.__isset.spec_int64;
    if((Spec_double != null) && __isset.spec_double)
    {
      tmp125.Spec_double = (SpecValueSerial_DOUBLE)this.Spec_double.DeepCopy();
    }
    tmp125.__isset.spec_double = this.__isset.spec_double;
    if((Spec_bytes != null) && __isset.spec_bytes)
    {
      tmp125.Spec_bytes = (SpecValueSerial_BYTES)this.Spec_bytes.DeepCopy();
    }
    tmp125.__isset.spec_bytes = this.__isset.spec_bytes;
    if((Spec_key != null) && __isset.spec_key)
    {
      tmp125.Spec_key = (SpecValueSerial_KEY)this.Spec_key.DeepCopy();
    }
    tmp125.__isset.spec_key = this.__isset.spec_key;
    if((Spec_li != null) && __isset.spec_li)
    {
      tmp125.Spec_li = (SpecValueSerial_LI)this.Spec_li.DeepCopy();
    }
    tmp125.__isset.spec_li = this.__isset.spec_li;
    if((Spec_lb != null) && __isset.spec_lb)
    {
      tmp125.Spec_lb = (SpecValueSerial_LB)this.Spec_lb.DeepCopy();
    }
    tmp125.__isset.spec_lb = this.__isset.spec_lb;
    return tmp125;
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
              Spec_int64 = new SpecValueSerial_INT64();
              await Spec_int64.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 3:
            if (field.Type == TType.Struct)
            {
              Spec_double = new SpecValueSerial_DOUBLE();
              await Spec_double.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 4:
            if (field.Type == TType.Struct)
            {
              Spec_bytes = new SpecValueSerial_BYTES();
              await Spec_bytes.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 5:
            if (field.Type == TType.Struct)
            {
              Spec_key = new SpecValueSerial_KEY();
              await Spec_key.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 6:
            if (field.Type == TType.Struct)
            {
              Spec_li = new SpecValueSerial_LI();
              await Spec_li.ReadAsync(iprot, cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 7:
            if (field.Type == TType.Struct)
            {
              Spec_lb = new SpecValueSerial_LB();
              await Spec_lb.ReadAsync(iprot, cancellationToken);
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
      var tmp126 = new TStruct("SpecValueSerialField");
      await oprot.WriteStructBeginAsync(tmp126, cancellationToken);
      var tmp127 = new TField();
      if(__isset.field_id)
      {
        tmp127.Name = "field_id";
        tmp127.Type = TType.I32;
        tmp127.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp127, cancellationToken);
        await oprot.WriteI32Async(Field_id, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Spec_int64 != null) && __isset.spec_int64)
      {
        tmp127.Name = "spec_int64";
        tmp127.Type = TType.Struct;
        tmp127.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp127, cancellationToken);
        await Spec_int64.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Spec_double != null) && __isset.spec_double)
      {
        tmp127.Name = "spec_double";
        tmp127.Type = TType.Struct;
        tmp127.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp127, cancellationToken);
        await Spec_double.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Spec_bytes != null) && __isset.spec_bytes)
      {
        tmp127.Name = "spec_bytes";
        tmp127.Type = TType.Struct;
        tmp127.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp127, cancellationToken);
        await Spec_bytes.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Spec_key != null) && __isset.spec_key)
      {
        tmp127.Name = "spec_key";
        tmp127.Type = TType.Struct;
        tmp127.ID = 5;
        await oprot.WriteFieldBeginAsync(tmp127, cancellationToken);
        await Spec_key.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Spec_li != null) && __isset.spec_li)
      {
        tmp127.Name = "spec_li";
        tmp127.Type = TType.Struct;
        tmp127.ID = 6;
        await oprot.WriteFieldBeginAsync(tmp127, cancellationToken);
        await Spec_li.WriteAsync(oprot, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Spec_lb != null) && __isset.spec_lb)
      {
        tmp127.Name = "spec_lb";
        tmp127.Type = TType.Struct;
        tmp127.ID = 7;
        await oprot.WriteFieldBeginAsync(tmp127, cancellationToken);
        await Spec_lb.WriteAsync(oprot, cancellationToken);
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
    if (!(that is SpecValueSerialField other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.field_id == other.__isset.field_id) && ((!__isset.field_id) || (global::System.Object.Equals(Field_id, other.Field_id))))
      && ((__isset.spec_int64 == other.__isset.spec_int64) && ((!__isset.spec_int64) || (global::System.Object.Equals(Spec_int64, other.Spec_int64))))
      && ((__isset.spec_double == other.__isset.spec_double) && ((!__isset.spec_double) || (global::System.Object.Equals(Spec_double, other.Spec_double))))
      && ((__isset.spec_bytes == other.__isset.spec_bytes) && ((!__isset.spec_bytes) || (global::System.Object.Equals(Spec_bytes, other.Spec_bytes))))
      && ((__isset.spec_key == other.__isset.spec_key) && ((!__isset.spec_key) || (global::System.Object.Equals(Spec_key, other.Spec_key))))
      && ((__isset.spec_li == other.__isset.spec_li) && ((!__isset.spec_li) || (global::System.Object.Equals(Spec_li, other.Spec_li))))
      && ((__isset.spec_lb == other.__isset.spec_lb) && ((!__isset.spec_lb) || (global::System.Object.Equals(Spec_lb, other.Spec_lb))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.field_id)
      {
        hashcode = (hashcode * 397) + Field_id.GetHashCode();
      }
      if((Spec_int64 != null) && __isset.spec_int64)
      {
        hashcode = (hashcode * 397) + Spec_int64.GetHashCode();
      }
      if((Spec_double != null) && __isset.spec_double)
      {
        hashcode = (hashcode * 397) + Spec_double.GetHashCode();
      }
      if((Spec_bytes != null) && __isset.spec_bytes)
      {
        hashcode = (hashcode * 397) + Spec_bytes.GetHashCode();
      }
      if((Spec_key != null) && __isset.spec_key)
      {
        hashcode = (hashcode * 397) + Spec_key.GetHashCode();
      }
      if((Spec_li != null) && __isset.spec_li)
      {
        hashcode = (hashcode * 397) + Spec_li.GetHashCode();
      }
      if((Spec_lb != null) && __isset.spec_lb)
      {
        hashcode = (hashcode * 397) + Spec_lb.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp128 = new StringBuilder("SpecValueSerialField(");
    int tmp129 = 0;
    if(__isset.field_id)
    {
      if(0 < tmp129++) { tmp128.Append(", "); }
      tmp128.Append("Field_id: ");
      Field_id.ToString(tmp128);
    }
    if((Spec_int64 != null) && __isset.spec_int64)
    {
      if(0 < tmp129++) { tmp128.Append(", "); }
      tmp128.Append("Spec_int64: ");
      Spec_int64.ToString(tmp128);
    }
    if((Spec_double != null) && __isset.spec_double)
    {
      if(0 < tmp129++) { tmp128.Append(", "); }
      tmp128.Append("Spec_double: ");
      Spec_double.ToString(tmp128);
    }
    if((Spec_bytes != null) && __isset.spec_bytes)
    {
      if(0 < tmp129++) { tmp128.Append(", "); }
      tmp128.Append("Spec_bytes: ");
      Spec_bytes.ToString(tmp128);
    }
    if((Spec_key != null) && __isset.spec_key)
    {
      if(0 < tmp129++) { tmp128.Append(", "); }
      tmp128.Append("Spec_key: ");
      Spec_key.ToString(tmp128);
    }
    if((Spec_li != null) && __isset.spec_li)
    {
      if(0 < tmp129++) { tmp128.Append(", "); }
      tmp128.Append("Spec_li: ");
      Spec_li.ToString(tmp128);
    }
    if((Spec_lb != null) && __isset.spec_lb)
    {
      if(0 < tmp129++) { tmp128.Append(", "); }
      tmp128.Append("Spec_lb: ");
      Spec_lb.ToString(tmp128);
    }
    tmp128.Append(')');
    return tmp128.ToString();
  }
}

