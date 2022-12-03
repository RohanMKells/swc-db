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
/// Serial BYTES Field Update
/// </summary>
public partial class FU_BYTES : TBase
{
  private sbyte _ctrl;
  private FU_LIST_OP _op;
  private int _pos;
  private Comp _comp;
  private byte[] _v;

  public sbyte Ctrl
  {
    get
    {
      return _ctrl;
    }
    set
    {
      __isset.ctrl = true;
      this._ctrl = value;
    }
  }

  /// <summary>
  /// 
  /// <seealso cref="global::.FU_LIST_OP"/>
  /// </summary>
  public FU_LIST_OP Op
  {
    get
    {
      return _op;
    }
    set
    {
      __isset.op = true;
      this._op = value;
    }
  }

  public int Pos
  {
    get
    {
      return _pos;
    }
    set
    {
      __isset.pos = true;
      this._pos = value;
    }
  }

  /// <summary>
  /// 
  /// <seealso cref="global::.Comp"/>
  /// </summary>
  public Comp Comp
  {
    get
    {
      return _comp;
    }
    set
    {
      __isset.comp = true;
      this._comp = value;
    }
  }

  public byte[] V
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


  public Isset __isset;
  public struct Isset
  {
    public bool ctrl;
    public bool op;
    public bool pos;
    public bool comp;
    public bool v;
  }

  public FU_BYTES()
  {
    this._ctrl = 0;
    this.__isset.ctrl = true;
    this._op = FU_LIST_OP.REPLACE;
    this.__isset.op = true;
  }

  public FU_BYTES DeepCopy()
  {
    var tmp336 = new FU_BYTES();
    if(__isset.ctrl)
    {
      tmp336.Ctrl = this.Ctrl;
    }
    tmp336.__isset.ctrl = this.__isset.ctrl;
    if(__isset.op)
    {
      tmp336.Op = this.Op;
    }
    tmp336.__isset.op = this.__isset.op;
    if(__isset.pos)
    {
      tmp336.Pos = this.Pos;
    }
    tmp336.__isset.pos = this.__isset.pos;
    if(__isset.comp)
    {
      tmp336.Comp = this.Comp;
    }
    tmp336.__isset.comp = this.__isset.comp;
    if((V != null) && __isset.v)
    {
      tmp336.V = this.V.ToArray();
    }
    tmp336.__isset.v = this.__isset.v;
    return tmp336;
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
            if (field.Type == TType.Byte)
            {
              Ctrl = await iprot.ReadByteAsync(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 2:
            if (field.Type == TType.I32)
            {
              Op = (FU_LIST_OP)await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 3:
            if (field.Type == TType.I32)
            {
              Pos = await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 4:
            if (field.Type == TType.I32)
            {
              Comp = (Comp)await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 5:
            if (field.Type == TType.String)
            {
              V = await iprot.ReadBinaryAsync(cancellationToken);
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
      var tmp337 = new TStruct("FU_BYTES");
      await oprot.WriteStructBeginAsync(tmp337, cancellationToken);
      var tmp338 = new TField();
      if(__isset.ctrl)
      {
        tmp338.Name = "ctrl";
        tmp338.Type = TType.Byte;
        tmp338.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp338, cancellationToken);
        await oprot.WriteByteAsync(Ctrl, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.op)
      {
        tmp338.Name = "op";
        tmp338.Type = TType.I32;
        tmp338.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp338, cancellationToken);
        await oprot.WriteI32Async((int)Op, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.pos)
      {
        tmp338.Name = "pos";
        tmp338.Type = TType.I32;
        tmp338.ID = 3;
        await oprot.WriteFieldBeginAsync(tmp338, cancellationToken);
        await oprot.WriteI32Async(Pos, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if(__isset.comp)
      {
        tmp338.Name = "comp";
        tmp338.Type = TType.I32;
        tmp338.ID = 4;
        await oprot.WriteFieldBeginAsync(tmp338, cancellationToken);
        await oprot.WriteI32Async((int)Comp, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((V != null) && __isset.v)
      {
        tmp338.Name = "v";
        tmp338.Type = TType.String;
        tmp338.ID = 5;
        await oprot.WriteFieldBeginAsync(tmp338, cancellationToken);
        await oprot.WriteBinaryAsync(V, cancellationToken);
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
    if (!(that is FU_BYTES other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.ctrl == other.__isset.ctrl) && ((!__isset.ctrl) || (global::System.Object.Equals(Ctrl, other.Ctrl))))
      && ((__isset.op == other.__isset.op) && ((!__isset.op) || (global::System.Object.Equals(Op, other.Op))))
      && ((__isset.pos == other.__isset.pos) && ((!__isset.pos) || (global::System.Object.Equals(Pos, other.Pos))))
      && ((__isset.comp == other.__isset.comp) && ((!__isset.comp) || (global::System.Object.Equals(Comp, other.Comp))))
      && ((__isset.v == other.__isset.v) && ((!__isset.v) || (TCollections.Equals(V, other.V))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.ctrl)
      {
        hashcode = (hashcode * 397) + Ctrl.GetHashCode();
      }
      if(__isset.op)
      {
        hashcode = (hashcode * 397) + Op.GetHashCode();
      }
      if(__isset.pos)
      {
        hashcode = (hashcode * 397) + Pos.GetHashCode();
      }
      if(__isset.comp)
      {
        hashcode = (hashcode * 397) + Comp.GetHashCode();
      }
      if((V != null) && __isset.v)
      {
        hashcode = (hashcode * 397) + V.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp339 = new StringBuilder("FU_BYTES(");
    int tmp340 = 0;
    if(__isset.ctrl)
    {
      if(0 < tmp340++) { tmp339.Append(", "); }
      tmp339.Append("Ctrl: ");
      Ctrl.ToString(tmp339);
    }
    if(__isset.op)
    {
      if(0 < tmp340++) { tmp339.Append(", "); }
      tmp339.Append("Op: ");
      Op.ToString(tmp339);
    }
    if(__isset.pos)
    {
      if(0 < tmp340++) { tmp339.Append(", "); }
      tmp339.Append("Pos: ");
      Pos.ToString(tmp339);
    }
    if(__isset.comp)
    {
      if(0 < tmp340++) { tmp339.Append(", "); }
      tmp339.Append("Comp: ");
      Comp.ToString(tmp339);
    }
    if((V != null) && __isset.v)
    {
      if(0 < tmp340++) { tmp339.Append(", "); }
      tmp339.Append("V: ");
      V.ToString(tmp339);
    }
    tmp339.Append(')');
    return tmp339.ToString();
  }
}

