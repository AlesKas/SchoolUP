using HW8.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace HW8.Controllers
{
    public class StudentController : BaseController
    {
        public ActionResult All()
        {
            List<Student> students = Ctx.Students.ToList();
            ViewBag.Blekeke = "tralala";
            return View(students);
        }

        [HttpGet]
        public ActionResult Edit(int id)
        {
            Student s = Ctx.Students.FirstOrDefault(p => p.Id == id);
            if (s != null)
            {
                return View(s);
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }

        [HttpPost]
        public ActionResult Edit(Student studentEdited)
        {
            Student s = Ctx.Students.FirstOrDefault(p => p.Id == studentEdited.Id);
            Address a = studentEdited.Address;
            if (s != null)
            {
                s.Name = studentEdited.Name;
                s.Surname = studentEdited.Surname;
                s.Rocnik = studentEdited.Rocnik;
                s.Address.City = studentEdited.Address.City;
                s.Address.Street = studentEdited.Address.Street;
                s.Address.Number = studentEdited.Address.Number;
                Ctx.SaveChanges();
                return RedirectToAction("All");
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }

        [HttpGet]
        public ActionResult Add()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Add(Student studentAdd)
        {
            Address a = studentAdd.Address;
            Ctx.Students.Add(studentAdd);
            a.City = studentAdd.Address.City;
            a.Street = studentAdd.Address.Street;
            a.Number = studentAdd.Address.Number;
            Ctx.Addresses.Add(a);
            Ctx.SaveChanges();
            return RedirectToAction("All");
        }

        [HttpGet]
        public ActionResult Delete(Student studentDelete)
        {
            Student s = Ctx.Students.FirstOrDefault(p => p.Id == studentDelete.Id);
            Address a = Ctx.Addresses.FirstOrDefault(p => p.Id == s.Address.Id);
            if (s != null)
            {
                Ctx.Students.Remove(s);
                Ctx.Addresses.Remove(a);
                Ctx.SaveChanges();
                return RedirectToAction("All");
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }

        [HttpGet]
        public ActionResult Detail(int id)
        {
            Student s = Ctx.Students.FirstOrDefault(p => p.Id == id);
            if (s != null)
            {
                return View(s);
            }
            else
            {
                return new HttpNotFoundResult("Student not found");
            }
        }
    }
}